# lingva-api

Simple header only client to any instance of lingva translator. Includes basic functions such as translation and display of available languages.

## Installation
### Install dependencies
```
sudo pacman -S core/curl extra/nlohmann-json
```
### Just include this header file to the project.

```cpp
#include "lingva-api/include/lingva.hpp"
```

## Usage
```
// Initialize client
lingvaClient client;

std::string sampleSentence = "Hello world!";
std::string sampleSentencePL = "Witaj świecie!";

// Get languages
client.getLanguages();

// List languages (will work without getLanguages)
client.listLanguages();

// Translate without provided source nor target
std::cout << client.translate(sampleSentencePL) << '\n';

// Translate to different available languages
std::cout << client.translate(sampleSentence, "en", "pl") << '\n';
std::cout << client.translate(sampleSentence, "en", "ru") << '\n';
std::cout << client.translate(sampleSentence, "en", "de") << '\n';
std::cout << client.translate(sampleSentence, "en", "hu") << '\n';

// Handle error
std::string getTranslation = client.translate(sampleSentence, "en", "error");
if (getTranslation.length())
std::cout << "Success";
else
std::cout << "Error";
```