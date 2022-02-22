# VoIP-with-Voice-Changer

## Install required libraries
#### First, install `netcat` and `sox`
- For mac users, install homebrew and run

```
brew install netcat
brew install sox
```

- For linux users, run 
```
sudo apt install netcat
sudo apt install sox
```
---------------------------------------
## Setup IP address
#### Run `ifconfig` on the server to get the server IP address. Open `client.sh`, replace `0.0.0.0` with the server IP address.

---------------------------------------


## Run the application
#### On the server machine, run `server.sh`.
#### On the client machine, run `client.sh`.