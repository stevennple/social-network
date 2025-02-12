all: social_network

post.o: post.cpp post.h
	g++ -Wall -std=c++11 -c post.cpp -o post.o

user.o: user.cpp user.h
	g++ -Wall -std=c++11 -c user.cpp -o user.o
	
network.o: network.cpp network.h user.h
	g++ -Wall -std=c++11 -c network.cpp -o network.o

social_network.o: social_network.cpp network.h user.h
	g++ -Wall -std=c++11 -c social_network.cpp -o social_network.o

# Link the object files to create the executable
social_network: post.o user.o network.o social_network.o
	g++ -Wall -std=c++11 post.o user.o network.o social_network.o -o social_network

# Clean up the object files and the executable
clean:
	rm -f *.o social_network