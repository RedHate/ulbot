/*
 *	UltrosIRC - 2021
 * 		command line irc bot.
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <regex.h>

int regcmp(const char *str, char *pattern){

	regex_t re;
	if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0)   return 0;
	int ret = regexec(&re, str, (size_t) 0, NULL, 0);
	regfree(&re);
	if (ret != 0) return 0;

	return 1;
}

int main(int argc, char *argv[]){

	if (argc < 4){
		fprintf(stderr,"usage %s <ip/hostname> <port> <channel> <nick>\n", argv[0]);
		exit(0);
	}

	//vars for sockets
	struct sockaddr_in t_socket;

	//open the socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){ 
		printf("ERROR opening socket");
		exit(0);
	}

	//get the server address
	struct hostent *t_server = gethostbyname(argv[1]);
	if (t_server == NULL){
		printf("ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &t_socket, sizeof(t_socket));
	t_socket.sin_family = AF_INET;
	bcopy((char *)t_server->h_addr,(char *)&t_socket.sin_addr.s_addr, t_server->h_length);
	t_socket.sin_port = htons(atoi(argv[2]));

	if (connect(sockfd,(struct sockaddr *) &t_socket,sizeof(t_socket)) < 0){
		printf("ERROR connecting\n");
		exit(0);
	}

	unsigned char buf[512];

	sprintf(buf, "USER but guest moon sun\n\
				  NICK %s\n\
				  JOIN #%s\n", argv[4], argv[3]);
	write(sockfd,buf,strlen(buf));

	int running = 1;
	while(running){

		int n = read(sockfd,buf,sizeof(buf));
		if(n){
			if(regcmp(buf, "PRIVMSG .* :.fuck")){
				unsigned char new[512];
				sprintf(new, "PRIVMSG #%s :ACTION fucks the air.\n", argv[3]);
				write(sockfd,new,strlen(new));
			}
			if(regcmp(buf, "PRIVMSG .* :.bang")){
				unsigned char new[512];
				sprintf(new, "PRIVMSG #%s :ACTION shoots back.\n", argv[3]);
				write(sockfd,new,strlen(new));
			}
			if(regcmp(buf, "PRIVMSG .* :.rage")){
				unsigned char new[512];
				sprintf(new, "PRIVMSG #%s :*EXPLODES ATOMIC HELL FIRE!* ROAAAAAR!\n", argv[3]);
				write(sockfd,new,strlen(new));
			}
			if(regcmp(buf, "PRIVMSG .* :.shakeitbaby")){
				unsigned char new[512];
				sprintf(new, "PRIVMSG #%s :You wanna dance?\n", argv[3]);
				write(sockfd,new,strlen(new));
			}
			if(regcmp(buf, "PRIVMSG .* :.quit")){
				unsigned char new[512];
				sprintf(new, "PART #chat \n\
							  QUIT \n");
				write(sockfd,new,strlen(new));
				running = 0;
			}
			if(regcmp(buf, "PING.*")){ //should resolve host name and but placed into a buffer
				write(sockfd, "PONG\n", 5);
			}
			for(int i=0; i<n; i++){
				printf("%c", buf[i]);
			}
		}
	}

    close(sockfd);
    
    return 0;

}

