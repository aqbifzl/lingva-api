# lingva-api

Simple header only client to any instance of lingva translator. Includes basic functions such as translation and display of available languages.

## Installation
### Install dependencies
#### Arch-based distro
```
sudo pacman -S core/curl extra/nlohmann-json
```
#### Debian-based distro
```
sudo apt install libcurl-dev nlohmann-json-dev
```

### Just include this header file to the project.

```cpp
#include "lingva-api/include/lingva.hpp"
```
> **Warning**
> This library requires adding curl at compile time, add -lcurl flag.

## Usage
#### Initialize client
```cpp
lingvaClient client;
//OR with default source language
lingvaClient client("auto");
//OR with default source and target language
lingvaClient client("auto", "hu");
//OR with default source and target language and custom instance
lingvaClient client("auto", "hu", "lingva.ml");
```
#### Get all available languages
```cpp
client.getLanguages();
```
> They are stored in public class member "languages" which is a vector std::vector<std::pair<std::string, std::string>> where first element is the full name and the second is the code.
#### List all languages in human-readable format (automatically calld getLanguages() when it is empty)
```cpp
client.listLanguages();
```
#### Translate passed sentence
```cpp
client.translate("Witaj świecie!");
```
> Uses values from the initializer, or "auto" as source and "en" as target if nothing were specified in initializer
#### Translate passed sentence with custom language options
```cpp
client.translate("Hello world!", "en", "ru");
```
#### Handle error
```cpp
std::string getTranslation = client.translate(sampleSentence, "en", "error");
 if (getTranslation.length())
   std::cout << "Success";
 else
   std::cout << "Error";
```
> Simply empty result means error