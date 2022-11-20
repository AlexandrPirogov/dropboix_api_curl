#include "RequestHandler.h"

RequestHandler::RequestHandler(char* accessCodeFileName)
{

    curl_global_init(CURL_GLOBAL_DEFAULT);
    dropboxUrls = std::make_unique<DropboxUrlContainer>();
    if(!bearerIsExists())
        initBearer(accessCodeFileName);
};


void RequestHandler::handleRequest(class GetCommand* command)
{
    if(!checkFileExistingOnDropbox(command->srcPath()))
    {
        std::string PathError = "\n\n\n+-------------ERROR!----------------+\n";
        PathError +=                  "|Given path not found on DropBox! :c|\n";
        PathError +=                  "+-----------------------------------+\n";
        throw std::runtime_error(PathError);
    }
        
    auto curl = curl_easy_init();
    string response_string;
    string header_string;
    std::string dropboxPath = dropboxPathGetCommand(command->srcPath());
    if (curl) {
        //file path
        fp = fopen(command->dstPath().c_str(), "wb");
        
 //Appending headers
        headers = curl_slist_append(headers, authorizationCurlHeader().c_str());
        headers = curl_slist_append(headers, dropboxPath.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

        //setting curl options for correct request handle
        curl_easy_setopt(curl, CURLOPT_URL, dropboxUrls->find(DROPBOX_API_URLS::DOWNLOAD_FILE)); 
        //curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BEARER);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        executeCurl(curl);
        fclose(fp);
    }
};

void RequestHandler::handleRequest(class PutCommand* command)
{

    std::string givenPath = std::filesystem::path(command->dstPath()).remove_filename();

    if(!checkFileExistingOnDropbox(givenPath.substr(0, givenPath.size()-1)))
    {
        std::string PathError = "\n\n\n+-------------ERROR!----------------+\n";
        PathError +=                  "|Given path not found on DropBox! :c|\n";
        PathError +=                  "+-----------------------------------+\n";
        throw std::runtime_error(PathError);
    }

    auto curl = curl_easy_init();
    std::string dropboxPath = dropboxPathPutCommand(command->dstPath());
    std::cout << command->srcPath() << '\n';
    if (curl) {
        fp = fopen(command->srcPath().c_str(), "rb");

         if(fstat(fileno(fp), &file_info) != 0)
            throw std::runtime_error("Please, set your Access Code.\n You can get your code here: https://www.dropbox.com/oauth2/authorize?client_id=sv55ql8k090jinc&response_type=code\n");/* cannot continue */
       //Security issue
        headers = curl_slist_append(headers, authorizationCurlHeader().c_str());
        headers = curl_slist_append(headers, dropboxPath.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/octet-stream");

        curl_easy_setopt(curl, CURLOPT_URL, dropboxUrls->find(DROPBOX_API_URLS::UPLOAD_FILE));
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BEARER);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);

        executeCurl(curl);
        fclose(fp);
    }
};

//shitty stackoverflow copypaste
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool RequestHandler::bearerIsExists()
{
    std::ifstream bearerStream("bearer.txt");
    if(bearerStream.is_open())
    {
        getline(bearerStream, token);
        if(token.size() == 0)
        {
            bearerStream.close();
            return false;
        }
        return true;
    } else {
        bearerStream.close();
        return false;
    }
};

std::string RequestHandler::authorizationCurlHeader()
{
    string token_header = "Authorization: Bearer ";
    token_header += token;
    return token_header;
};    

void RequestHandler::executeCurl(CURL* curl)
{
        long http_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);
        std::string response_string;
        std::string header_string;
        try{
            
            std::string SuccessMessage = "\n\n\n+-------------OK!------------------+\n";
            SuccessMessage +=                  "|  Trying to make request... (>_>) |\n";
            SuccessMessage +=                  "+----------------------------------+\n";
            std::cout << SuccessMessage<<'\n';
            auto code = curl_easy_perform(curl);
            if(code != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(code));
            
            printResponse(response_string);
        }catch( const std::exception & ex ) {
            std::cout <<"Fail request...\n";
            std::cerr << ex.what() << '\n';
        }
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
};

void RequestHandler::initBearer(char* tokenFile)
{
    std::fstream ifstream(tokenFile);
    if(ifstream.is_open())
    {
        getline(ifstream, token);
        if(token.size() == 0)
            throw std::runtime_error("Please, set your Access Code.\n You can get your code here: https://www.dropbox.com/oauth2/authorize?client_id=sv55ql8k090jinc&response_type=code\n");
    } else {
        std::ofstream of(tokenFile);
        of.close();
        throw std::runtime_error("Please, set your Access Code.\n You can get your code here: https://www.dropbox.com/oauth2/authorize?client_id=sv55ql8k090jinc&response_type=code\n");
    }
    ifstream.close();

 
    std::string data = "code=";
    data += token;
    data +="&grant_type=authorization_code&client_id=sv55ql8k090jinc&client_secret=prb501blz2hzra3";
    auto curl = curl_easy_init();
    if (curl) {
        fp = fopen(tokenFile, "rb");

        curl_easy_setopt(curl, CURLOPT_URL, dropboxUrls->find(DROPBOX_API_URLS::RETRIEVE_BEARER));
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
 
        std::string response_string_json;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string_json);
        int code = curl_easy_perform(curl);
        json js = json::parse(response_string_json);
        std::ofstream of("bearer.txt");
        std::string bearer = js["access_token"];
        bearer.erase(std::remove( bearer.begin(), bearer.end(), '\"' ),bearer.end());
        token = bearer;
        of << bearer;
        of.close();
        executeCurl(curl);
    }
};


std::string  RequestHandler::dropboxPathPutCommand(const std::string& dropboxPath)
{
    //Here should be API-builder, but...
    string dropbox_path = std::string("Dropbox-API-Arg: {\"autorename\":false,\"mode\":\"add\",\"mute\":false,\"path\":\"");
    dropbox_path += dropboxPath;
    dropbox_path += "\",\"strict_conflict\":false}";
    return dropbox_path.c_str();
};

std::string RequestHandler::dropboxPathGetCommand(const std::string& dropboxPath)
{
    //Here should be API-builder, but...
    string dropbox_path = std::string("Dropbox-API-Arg: {\"path\":\"");
    dropbox_path += dropboxPath;
    dropbox_path += "\"}";
    return dropbox_path;
    
};

std::string RequestHandler::dropboxGetFileMetaCommand(const std::string& dropboxPath)
{
    //Here should be API-builder, but...
    std::string data = "{\"include_deleted\":false,\"include_has_explicit_shared_members\":false,\"include_media_info\":false,\"path\":\"";
    data += dropboxPath;
    data += "\"}";
    return data;
};

//Shit code
bool RequestHandler::checkFileExistingOnDropbox(std::string srcPath)
{
    auto curl = curl_easy_init();
    string response_string;
    string header_string;
    std::string dropboxPath = dropboxGetFileMetaCommand(srcPath);
    if (curl) {    
    //Appending headers
        headers = curl_slist_append(headers, authorizationCurlHeader().c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        //setting curl options for correct request handle
        curl_easy_setopt(curl, CURLOPT_URL, dropboxUrls->find(DROPBOX_API_URLS::FILE_METADATA)); 
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dropboxPath.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        std::cout << "\n\n\n+--------------------------------------+\n";
        std::cout << "|(<_<) Searching for given path (>_>)  |\n";
        std::cout << "+--------------------------------------+\n";
        auto code = curl_easy_perform(curl);

        try {
            json js = json::parse(response_string);
            std::string tmp = js["name"];
        } catch(...) {
            return false;
        }

        curl_easy_cleanup(curl);
        curl_global_cleanup();
        curl = NULL;
        headers = NULL;
    }
        std::cout << "\n\n\n+---------------OK!--------------+\n";
        std::cout << "|        We found it!  :)        |\n";
        std::cout << "+--------------------------------+\n";
    return true;
};

void RequestHandler::printResponse(std::string response)
{
    json js;
    try{
        js = json::parse(response);
    } catch(const std::exception& ex)
    {
       // std::cout << "Seems like we've got not an json...\n";
    }


    std::string SuccessMessage = "\n\n\n+----------------OK!---------------+\n";
    SuccessMessage +=                  "|           We did it (^_^)        |\n";
    SuccessMessage +=                  "+----------------------------------+\n";
    std::cout << SuccessMessage<<'\n';
};