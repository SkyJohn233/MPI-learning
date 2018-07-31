#include<iostream>
#include<string>
#include<mpi.h>
#include<cstdio>
#include<cstring>
using std::string;


int main(int argc,char *argv[]) {
	MPI_Status status;
	int myid,numprocess;
	char message[1000];
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocess);
	if(myid!=0) {
		sprintf(message,"hello from process %d",myid);
		MPI_Send(message,strlen(message)+1,MPI_CHAR,0,99,MPI_COMM_WORLD);
	}
	else {
		for(int source=1;source<numprocess;++source) {
			MPI_Recv(message,1000,MPI_CHAR,source,99,MPI_COMM_WORLD,&status);
			printf("%d\n",status );
			printf("%s\n",message);
		}
	}
	MPI_Finalize();
	return 0;
}