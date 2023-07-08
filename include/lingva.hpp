#ifndef __LINGVA_API__
#define __LINGVA_API__
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

class lingvaClient {
public:
  lingvaClient(std::string source = "auto", std::string target = "en",
               std::string lingvaInstance = "lingva.ml")
      : source(source), target(target), lingvaInstance(lingvaInstance),
        curl(curl_easy_init()) {}
  ~lingvaClient() {
    if (curl)
      curl_easy_cleanup(curl);
  }

  std::vector<std::pair<std::string, std::string>> languages;

  void listLanguages() {
    if (languages.empty())
      getLanguages();
    for (const auto &lang : languages) {
      std::cout << lang.first << " - " << lang.second << '\n';
    }
  }

  void getLanguages() {
    std::string url = "https://" + lingvaInstance + "/api/v1/languages";

    nlohmann::json result = makeRequest(url);
    try {
      for (const auto &lang : result["languages"]) {
        languages.push_back(
            {lang["name"].get<std::string>(), lang["code"].get<std::string>()});
      }
    } catch (const nlohmann::json::exception &e) {
      std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
  }

  std::string translate(const std::string &text, const std::string &cSource,
                        const std::string &cTarget) {
    std::string url = "https://" + lingvaInstance + "/api/v1/" + cSource + '/' +
                      cTarget + "/";
    url.append(curl_easy_escape(curl, text.c_str(), text.length()));

    try {
      nlohmann::json result = makeRequest(url);
      return result["translation"];
    } catch (const nlohmann::json::exception &e) {
      std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
    return std::string();
  }

  std::string translate(const std::string &text) {
    return translate(text, source, target);
  }

private:
  nlohmann::json makeRequest(std::string &url) {
    if (curl) {
      std::string result;
      CURLcode res;
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

      res = curl_easy_perform(curl);
      return nlohmann::json::parse(result);
      curl_easy_cleanup(curl);
    }
    return std::string();
  }
  std::string source;
  std::string lingvaInstance;
  std::string target;
  CURL *curl;
};

#endif