#include<stdio.h>
#include<pthread.h>
#include<string.h>
/*Un vector de saldo en cuentas, se indexa por número de cuenta*/
float* account_balances;

/*Transferimos DOLLARS de la cuenta FROM_ACCT a la cuenta 
TO_ACCT. Retornamos 0 si la operaciónfue exitosa, 
o 1 si el saldo de FROM_ACCT no es suficiente*/
typedef struct parametros{
	int cuenta_desde, cuenta_hasta;
	float dollars;
}par;

int process_transaction(int from_acct, int to_acct, float dollars){
	int old_cancel_state;
	/*Controlamos el saldo de FROM_ACCT*/
	if(account_balances[from_acct] < dollars)
		return 1;
	/*Inicio de la sección crítica*/
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	/*Movemos el dinero*/
	account_balances[to_acct] += dollars;
	account_balances [from_acct] -= dollars;
	/*Fin de la sección crítica*/
	return 0;
}


void * thread_transaction (void * args){
	par *p = (par*)args;
	process_transaction(p->cuenta_desde, p->cuenta_hasta, p->dollars);
}


int main(){
	pthread_t hilo;
	pthread_t hilo2;
	float balances[] = {2000, 10000, 2300, 4100};
	account_balances = balances;
	par transaccion_1, transaccion_2;
	transaccion_1.cuenta_desde = 2;
	transaccion_2.cuenta_desde = 0;
	transaccion_1.cuenta_hasta = 3;
	transaccion_2.cuenta_hasta = 1;
	transaccion_1.dollars = 230;
	transaccion_2.dollars = 40004;


	if(pthread_create(&hilo, NULL, &thread_transaction, &transaccion_1)){
		printf("Transacción 1 realizada con éxito\n");
		printf("La cuenta 1 tiene ahora %f$ y la cuenta 2 tiene ahora %f$\n", account_balances[transaccion_1.cuenta_desde], account_balances[transaccion_1.cuenta_hasta]);
	}else{
		printf("Transacción 1 no realizada\n");
	}
	if(pthread_create(&hilo2, NULL, &thread_transaction, &transaccion_2)){
		printf("Transacción 2 realizada con éxito\n");
				printf("La cuenta 1 tiene ahora %f$ y la cuenta 2 tiene ahora %f$\n", account_balances[transaccion_2.cuenta_desde], account_balances[transaccion_2.cuenta_hasta]);
	}else{
		printf("Transacción 2 no realizada\n");
	}

	return 0;
}
