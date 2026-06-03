#!/bin/bash

NBTEST=0
NBSUCCESS=0
NBFAILURE=0

FLAG=$1

ANALIZEFILES=("basic 1" "basic 2" "basic 3" "basic 5" "basic 10" "complex 3"\
            "untitled 1" "3waveslong 3" "3wavesverylong 3" "3waves 3" "4waves 4")
CRYPTFILES=("basic hello" "basic 123" "basic 123mix123" "basic \"space char\"" "basic \"special char*^!+]°\""\
            "complex hi" "untitled faaa" "3wavesverylong \"very long\"" "4waves 4waves.wav")

make > /dev/urandom

success() {
    NBTEST=$(($NBTEST + 1))
    NBSUCCESS=$(($NBSUCCESS + 1))
    echo -e "\e[0;32mTest n°$NBTEST succeded.\e[0;0m"
}

failure() {
    NBTEST=$(($NBTEST + 1))
    NBFAILURE=$(($NBFAILURE + 1))
    echo -e "\e[0;31mTest n°$NBTEST failed.\e[0;0m"
}

switch() {
    echo -e "\e[0;36m=======Mode $1=======\e[0;0m"
}

testAnalize() {
    SOUND="tests/testSounds/$1.wav"
    COMMAND="./stone_analysis -a $SOUND $2"
    
    if [ "$FLAG" = "-v" ]; then
        echo "Executing \"$COMMAND\""
    fi

    OUTPUT="$($COMMAND)"
    EXPECTED="$(cat tests/expectedOutput/$1-$2.txt)"

    if [ "$OUTPUT" = "$EXPECTED" ]; then
        success
    else
        failure
        echo -e "\e[0;33mExpected:\n$EXPECTED\e[0;0m"
        echo -e "\e[0;33mGot:\n$OUTPUT\e[0;0m"
    fi
}

testCrypt() {
    rm -rf tmp.wav > /dev/urandom
    SOUND="tests/testSounds/$1.wav"
    COMMAND1="./stone_analysis -c $SOUND tmp.wav $2"
    COMMAND2="./stone_analysis -d tmp.wav"
    
    if [ "$FLAG" = "-v" ]; then
        echo "Executing \"$COMMAND1\""
        echo "Executing \"$COMMAND2\""
    fi

    $COMMAND1
    OUTPUT="$($COMMAND2)"

    if [ "$OUTPUT" = "${2^^}" ]; then
        success
    else
        failure
        echo -e "\e[0;33mExpected:\n${2^^}\e[0;0m"
        echo -e "\e[0;33mGot:\n$OUTPUT\e[0;0m"
    fi
}

switch "Analize"
for list in "${ANALIZEFILES[@]}"
do
    testAnalize ${list[0]} ${list[1]}
done

switch "Cryptography"
for list in "${CRYPTFILES[@]}"
do
    testCrypt ${list[0]} ${list[1]}
done

echo -e "\e[0;36mTotal: $NBTEST\e[0;0m || \e[0;32mSUCCESS: $NBSUCCESS\e[0;0m || \e[0;31mFAILURE: $NBFAILURE\e[0;0m"
