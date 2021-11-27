#include <iostream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#include <string>

//g++ -o curl_get curlget.cpp -lcurl -ljsoncpp

using namespace std;
size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

string getPhoneNumbers(string country, string phoneNumber) {
    //curl_global_init(CURL_GLOBAL_DEFAULT);
    std::regex space("[[:space:]]");
    country = std::regex_replace(country, space, "%20");
    std::string response_string;
    auto curl = curl_easy_init();
    if (curl) {

        string url = "https://jsonmock.hackerrank.com/api/countries?name=" + country;
        //url = string("https://jsonmock.hackerrank.com/api/countries?name=") + "Puerto%20Rico";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        curl_easy_perform(curl);
        //cout << response_string;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = nullptr;
    }

    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( response_string.c_str(), root );     //parse process
    if (!parsingSuccessful) {
        std::cout  << "Failed to parse"
               << reader.getFormattedErrorMessages();
        return "-1";
    }

    Json::Value callingCodes = root["data"][0]["callingCodes"];
    auto size = callingCodes.size();

    int max_len = 0;
    string prefix = callingCodes[size-1].asString();
    if (prefix.length() == 0) return "-1";
    string ans = "+" + prefix + " " + phoneNumber;
    return ans;
}


int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    string country;
    getline(cin, country);

    string phoneNumber;
    getline(cin, phoneNumber);

    string result = getPhoneNumbers(country, phoneNumber);

    fout << result << "\n";

    fout.close();

    return 0;
}
