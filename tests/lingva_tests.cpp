#include "../include/lingva.hpp"

int main() {
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
}