# dropboix_api_curl

# Installation

Install required dependecies:
```sh
sudo apt-get install cmake g++ curl nlohmann-json3-dev libcurl4-gnutls-dev
```
----
```sh
1. Clone this repo
2. mkdir build && cd build
3. sudo cmake ../
4. sudo make
5. sudo make install
```
# How to start

If you'll run command first time, you'll get error, that bearer and access_token are not exist:

```sh
Please, set your Access Code. You can get your code here: https://www.dropbox.com/oauth2/authorize?client_id=sv55ql8k090jinc&response_type=code
```

Go here, press allow and you'll get your access code: [Get Access Code](https://www.dropbox.com/oauth2/authorize?client_id=sv55ql8k090jinc&response_type=code)

Copy code and save somewhere in text file. You'll need it to use commands!

# Commands

App can handle two commands:
## get -- to download file from Dropbox. Syntax:
```sh
dropbox <your_access_code_file> get <dropbox_path_to_file> <local_path>
```
### Example
```sh
dropbox_pi_cli user_token.txt get /Homework/book2.pdf ./book.pdf 
```

## put -- to upload file to Dropbox. Syntax:
```sh
dropbox <your_access_code_file> put <local_path> <dropbox_path_to_file>
```
### Example

```sh
dropbox_pi_cli user_token.txt put ./book.pdf /Homework/book2.pdf
```

----
