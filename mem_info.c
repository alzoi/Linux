// Определение скорости доступа к данным из кэша и из основной памяти.
// Определение размера кэша.
// gcc -g -Wall -o mem_info ./mem_info.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>

//#include <unistd.h>

unsigned long long time_rdtsc(int K){
// Измерение накладных расходов работы функции __rdtsc() в тактах процессора.
	unsigned long long t1, t2, t3, t4;	
	int i, min;
	
	min = 1000;
	t3=0;
	// Определяем минимальное значение замера времени.
	for(i=0; i<K; i++){
		t1 = __rdtsc();
		t2 = __rdtsc();
		t4 = t2 - t1;
		t3 += t4;
		if(t4 < min) min = t4;
	}
	t3 = t3 / K;
	printf("Накладные расходы измерения тактов процессора: среднее %llu, минимальное %u\n", t3, min);
	return t3;
}

int main(void) {
	volatile unsigned long long t1, t2;
	volatile int i, k;
	unsigned char *t_arr;
	int D, m;
	volatile int ofs;
	volatile unsigned char bt;
	volatile unsigned long long adr, adr0, adr1;
	time_t t;
	
	printf("Выделяем память 1024*1024*150 Байт\n");
	// Выделяем память.
	t_arr = (unsigned char *)malloc(1024*1024*150*sizeof(char));
	adr0 = (unsigned long long)((void *)(t_arr));
	adr1 = adr0 - (adr0 & 0xFFFFFFFFFFFFF000);

	D = 900;//3048;
	printf("Запись данных в память, при этом данные кэшируются на всех уровнях L1, L2, L3\n");
	printf("Число страниц %d по 4 КБ\n", D);
	for(i=0; i<D; i++){
		//ofs = rand() % (1609);	
		ofs = i;
		adr = 4096*ofs - adr1;
		t1 = __rdtsc();
		// Запись.
		t_arr[adr] = i;
		t2 = __rdtsc();
		//printf("%p %d, время %llu\n", (void *)(&t_arr[adr]), ofs, t2 - t1);			
	}
	printf("%p %d, время записи данных в память для последнего элемента %llu\n", (void *)(&t_arr[adr]), ofs, t2 - t1);			
	
	printf("\nВыполняем чтение из произвольных мест в памяти:\n");	
	// Случайно читаем 4096 байт.
	srand((unsigned) time(&t));
	//
	m = 0;
	for(i=1; i<D; i++){
		k = rand() % (D);	
		adr = 4096*k - adr1;
		t1 = __rdtsc();
		// Чтение.
		bt = t_arr[adr];
		t2 = __rdtsc();
		if( (t2 - t1) > 200 ) {
			m = 1;
			printf("данные не попали в кэш ~ время %llu k=%d   bt=%u\n", t2 - t1, k, bt);
		}
	}
	if(!m) {
		printf("ВСЕ ДАННЫЕ ЧИТАЮТСЯ ИЗ КЭША\n");		
	}
	// Чтение из кэша.
	printf("\nЧтение из кэша:\n");	
	k = 0;
	adr = 4096*k - adr1;
	t1 = __rdtsc();
	bt = t_arr[adr];
	t2 = __rdtsc();
	printf("~ время %llu k=%d   bt=%u\n", t2 - t1, k, bt);

	int f = getchar();

	return 0;
}
