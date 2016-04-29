
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

int thread_count;
bool* vector_block; /*= nullptr;*/
int* task_number; /*= nullptr;*/

int disponible_tasks=10;

void* exe(void* rank)
{
	long my_rank = (long) rank;
	
	while(disponible_tasks) /* Mientras que disponible tasks no es 0*/
	{
		while( vector_block[my_rank] && disponible_tasks );
		
		switch(task_number[my_rank])
		{
			case 1:
			{
				int suma = 4 + 19;
				cout<<("Suma:");
				cout<<suma<<endl;
				break;
			}
			case 2:
			{
				for(int i=0;i<10;++i);
					cout<<"hello"<<endl;
			}
		}

		task_number[my_rank] = 0; 
		vector_block[my_rank]=true;
	}
}

int main()
{
	bool salir=1;
	long thread;
	//Nro de threads
	thread_count = 3;
	
	vector_block = new bool[thread_count];
	task_number = new int[thread_count];
	
	//Inicializa los vectores con true and 0

	for(unsigned int i=0; i<thread_count; ++i)
	{
		vector_block[i]=true;
		task_number[i]=0;
	}

	pthread_t* thread_handles = new pthread_t[thread_count];
	
	/* Creamos los tread vector */
	for(thread=0; thread < thread_count; ++thread)
		pthread_create(&thread_handles[thread], NULL, exe,(void*) thread);
	
	int option=0;
	
	
	while(disponible_tasks)
	{
		cout<<"Menu"<<endl;
		cout<<"0. salir"<<endl;
		cout<<"1. Imprimir suma "<<endl;
		cout<<"2. Imprimir varios hola"<<endl;
		cout<<"3. imprimir threads sin trabajo "<<endl;
		cout<<"Tareas Disponibles: "<<disponible_tasks<<endl;
		cin>>option;
		
		switch(option){
			case 0:
			{
				disponible_tasks = 0;	
			}
			case 1:
			case 2:
			{
				salir = true;
				while(salir)
				{
					for(unsigned int i=0; i < (thread_count && salir); ++i)
					{
						if(task_number[i]==0)
						{
							task_number[i] = option;
							vector_block[i] = false;
							salir = false;
						}
					}
				}
				--disponible_tasks;

			}
			default:{
				for(unsigned int i=0;i<thread_count;++i)
				{
					if(vector_block[i])
					cout<<"thread ["<<i<<"] sin trabajo"<<endl;
				}	
			}		
		}
		
	}

	for(unsigned int thread = 0;thread < thread_count; ++thread)
		pthread_join(thread_handles[thread], NULL);
	
	delete(thread_handles);
	
	return 0;
}
