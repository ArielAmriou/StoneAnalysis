
# Steganography in StoneAnalysis

## What is Steganography ?

*Audio steganography is a method that camouflages a secret message inside an audio file* - USIM Research Repository

## Steganography methodes

### LSB

The LSB (Least significant bit) method consist in hiding characters in the lowest bit of an integer.

#### Code
Encryption
```c++
void StoneAnalysis::cypher()
{
    if (!_in)
        throw NotInitializeException();
    std::string msg = _msg + '\0';
    std::vector<int> bits;
    for (unsigned char c : msg)
        for (int i = NB_BITS - 1; i >= 0; --i)
            bits.push_back((c >> i) & 1);
    if (bits.size() > _in->_waves._data.size())
        throw MsgTooLongException();
    for (std::size_t i = 0; i < bits.size(); ++i)
        _in->_waves._data[i] = (_in->_waves._data[i] & ~1) | bits[i];
    _in->save(_out);
}
```

Decryption
```c++
void StoneAnalysis::decypher()
{
    if (!_in)
        throw NotInitializeException();
    std::string msg;
    std::size_t i = 0;
    while (i + NB_BITS <= _in->_waves._data.size()) {
        unsigned char c = 0;
        for (int b = NB_BITS - 1; b >= 0; --b)
            c |= (_in->_waves._data[i++] & 1) << b;
        if (c == '\0')
            break;
        msg += c;
    }
    std::cout << msg << "\n";
}
```

#### Audio file

[LSB Audio File](LSB.wav)

#### Limitation

Although we can correctly crypt and decrypt message in .wav audios, if we know the LSB was used to encrypt a message into a file, it is very simply decrypted.

### MSB

The MSB (Most significant bit) method consist in hiding characters in the highest bit of an integer.

#### Code
Encryption
```c++
void StoneAnalysis::cypher()
{
    if (!_in)
        throw NotInitializeException();
    std::string msg = _msg + '\0';
    std::vector<int> bits;
    for (unsigned char c : msg)
        for (int i = NB_BITS - 1; i >= 0; --i)
            bits.push_back((c >> i) & 1);
    if (bits.size() > _in->_waves._data.size())
        throw MsgTooLongException();
    for (std::size_t i = 0; i < bits.size(); ++i)
        _in->_waves._data[i] = (_in->_waves._data[i] & ~0b1000000000000000) | (bits[i] << 15);
    _in->save(_out);
}
```

Decryption
```c++
void StoneAnalysis::decypher()
{
    if (!_in)
        throw NotInitializeException();
    std::string msg;
    std::size_t i = 0;
    while (i + NB_BITS <= _in->_waves._data.size()) {
        unsigned char c = 0;
        for (int b = NB_BITS - 1; b >= 0; --b)
            c |= ((_in->_waves._data[i++] & 0b1000000000000000) >> 15) << b;
        if (c == '\0')
            break;
        msg += c;
    }
    std::cout << msg << "\n";
}
```

#### Audio file

[MSB Audio File](MSB.wav)

#### Limitation

This is clearly a bad method and should never be used. It is very clear that the audio file has been modified but is harder you decrypt because nobody uses MSB to encrypt files

### Other Methodes

As you could see, the LSB and MSB are not very secured and used, so, it would be better to uses DSSS, Echo Hiding, or even Spread Spectrum

[See mode about thoses methods](https://65610.csail.mit.edu/2024/reports/hong-kumar-huang.pdf)

## When is Steganograpy used

Steganograpy is used to hide message in all file format so that the message is decryptable and not humanly visible. It is vastly used in military, espionage and intelligence gathering

[Sources](https://www.acte.in/explained-what-is-steganography-technique#:~:text=Real%2DWorld%20Use%20Cases,-Steganography%20plays%20a&text=In%20the%20realm%20of%20cybersecurity,embedded%20in%20innocent%2Dlooking%20files.)