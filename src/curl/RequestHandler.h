#pragma once
#include <curl/curl.h>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include "./../Command.h"
#include "nlohmann/json.hpp"
#include <algorithm>

using json = nlohmann::json;

/**
 * Enum to escape writing URL as const char*
*/
enum DROPBOX_API_URLS
{
    DOWNLOAD_FILE, UPLOAD_FILE, RETRIEVE_BEARER, FILE_METADATA
};

/**
 * ATD that contains dropbox API URLS
*/
class DropboxUrlContainer
{
    std::unordered_map<DROPBOX_API_URLS, char*> dropboxUrls;
    public:
        DropboxUrlContainer()
        {
            dropboxUrls[DROPBOX_API_URLS::DOWNLOAD_FILE] = "https://content.dropboxapi.com/2/files/download";
            dropboxUrls[DROPBOX_API_URLS::UPLOAD_FILE] = "https://content.dropboxapi.com/2/files/upload";
            dropboxUrls[DROPBOX_API_URLS::RETRIEVE_BEARER] = "https://api.dropbox.com/oauth2/token";
            dropboxUrls[DROPBOX_API_URLS::FILE_METADATA] = "https://api.dropboxapi.com/2/files/get_metadata";
        };

        inline const char* find(DROPBOX_API_URLS key)
        {
            return dropboxUrls.find(key)->second;
        }
};

/**
 * Class handles request to dropbox API
 * Each method incapsulate request handle for specific API
*/
class RequestHandler
{
    std::string token;
    std::unique_ptr<DropboxUrlContainer> dropboxUrls;

    //Curl's stuff
    FILE *fp;
    struct stat file_info;
    struct curl_slist *headers= NULL;
    public:
        /**
         * Pre-condition: given existing file with access_code of user
         * Post-condition: user will be authed
        */
        RequestHandler(char* accessCodeFileName);
        /**
         * Pre-condition: given GetCommand
         * Post-condition: request is handled. Message will be outputed into terminal
        */
        void handleRequest(class GetCommand* cmd);

        /**
         * Pre-condition: given GetCommand
         * Post-condition: request is handled. Message will be outputed into terminal
        */
        void handleRequest(class PutCommand* command);
    private:
        /**
         * Pre-condition:
         * Post-condition: if file noe exists, it will be created with bearer token
        */
        bool bearerIsExists();

        /**
         * Pre-condition: given initializeed curl
         * Post-condition: request is executed. Message will be outputed into terminal 
        */
        void executeCurl(CURL* curl);

        /**
         * Pre-condition: given name of existing file with access User Code
         * Post-condition:
        */
        void initBearer(char*);

        /**
         * Pre-condition:
         * Post-condition: return authorization header for curl_easy_set_opts
        */
        std::string authorizationCurlHeader();

        /**
         * Pre-condition:
         * Post-condition: return authorization header for curl_easy_set_opts
        */
        std::string  dropboxPathPutCommand(const std::string& dropboxPath);

        /**
         * Pre-condition:
         * Post-condition: return authorization header for curl_easy_set_opts
        */
        std::string dropboxPathGetCommand(const std::string& dropboxPath);
        
        void printResponse(std::string response);

        bool checkFileExistingOnDropbox(std::string);

        std::string dropboxGetFileMetaCommand(const std::string& dropboxPath);
};