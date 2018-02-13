// Определение скорости доступа к данным из кэша и из основной памяти.
// gcc -g -Wall -o cpu_info ./cpu_info.c

#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>
#include <unistd.h>

unsigned long long time_rdtsc(void){
// Измерение накладных расходов работы функции __rdtsc() в тактах процессора.
	unsigned long long t1, t2, t3, t4;
	int K, i, min;
	K = 100000;
	min = 1000;
	// Определяем минимальное значение замера времени.
	for(i=0; i<K; i++){
		t1 = __rdtsc();
		t2 = __rdtsc();
		t4 = t2 - t1;
		t3 += t4;
		if(t4 < min) min = t4;
	}
	t3 = t3 / K;
	printf("Накладные расходы измерения тактов процессора: среднее %llu, минимальное %llu\n", t3, min);
	return t3;
}

void cpu_mhz(int sleeptime, unsigned long long t_rdt){
// Определение частоты процессора.
	unsigned long long t1, t2;
	double Mhz;
	t1 = __rdtsc();
	sleep(sleeptime);
	t2 = __rdtsc();
	t2 = t2 - t1 - t_rdt;
	Mhz = t2 / (1e6*sleeptime);
	printf("Частота процессора %.3f MHz\n", Mhz);		
}
void naprav(void) {
// Определяем, как процессор работает с памятью.
	// В памяти:
	// 1) int = 1 = 0x00000001 для остроконечника |> 0.
	// 2) int = 1 = 0x01000000 для тупоконечника  <| 0.	
	int __endian_bit = 1;
	if ((*(char*)&__endian_bit) == 0) {
		printf("тупоконечник  <| 0\n");
	}
	else {
		printf("остроконечник |> 0\n");		
	}
}

int main(void) {
	unsigned long long t_rdt, t1, t2;
	volatile int i, j;
	char *t_arr;
	unsigned long long adr, adr0, adr1;
	unsigned long m_adr[100];
	int m = 0, K;
	volatile char R;
	
	t_rdt = time_rdtsc();
	cpu_mhz(1, t_rdt);
	naprav();
	
	printf("\n");

	// Выделяем память.
	t_arr = (char *)malloc(1024*1024*40*sizeof(char));
	printf("Выделяем память (40 МБ)...\n");
	printf("Память выделена по адресу %p\n", t_arr);
	adr0 = (unsigned long long)((void *)(t_arr));
	adr1 = adr0 & 0xFFFFFFFFFFFFF000;
	printf("Память выделена по адресу %#llx (фактический адрес, с учётом выравнивания по границе страниц памяти 4 КБ)\n", adr1);
	printf("За это время заполняются кэши L1, L2, L3, в кэш-память записаны первые 4096 Байт (технология prefetch),\nпереданных кэш-строками по 64 Байта\n\n");
	adr1 = adr0 - adr1;
		
	printf("Чтение из области, которая попала в кэш\n");
	adr = 4096 - adr1 - 1;
	t1 = __rdtsc();
	t_arr[adr] = 3;
	t2 = __rdtsc();
	printf("%p => adr[%u] = %d, время доступа к памяти (DRAM) в тактах ядра процессора: %d\n\n", (void *)(&t_arr[adr]), adr, t_arr[adr], t2 - t1);	
	
	// Обращение к байту в памяти.
	printf("Читаем байты из выделенной памяти, которые не попали в кэш (шаг - страница памяти 4 КБ):\n");
	adr = 0;
	K = 20;
	for(i=0; i<K; i++){
		t1 = __rdtsc();
		t_arr[adr] = 9;
		t2 = __rdtsc();
		printf("%p => adr[%u] = %d, время доступа к памяти (DRAM) в тактах ядра процессора: %d\n", (void *)(&t_arr[adr]), adr, t_arr[adr], t2 - t1);
		// Обнуляем младшие 12 бит адреса adr1.
		adr0 = (unsigned long long)((void *)(&t_arr[adr]));
		adr1 = adr0 & 0xFFFFFFFFFFFFF000;	
		adr1 = adr0 - adr1;
		m_adr[i] = adr;	
		adr = adr + (0x1000 - adr1);
	}

	printf("\nПри чтении, байты попадают в кэш.\n");
	printf("Так как размер кэша L1d = 32 КБ, то туда поместится 8 страниц памяти, остальные страницы будут в L2.\n");
	
	printf("\nЧтение из кэша:\n");
	for(i=0; i<K; i++){
		// Чтение из кэша.
		adr = m_adr[i];
		t1 = __rdtsc();
		//R = t_arr[adr];// = i;
		t_arr[adr] = i;
		t2 = __rdtsc();
		printf("%p => adr[%u] = %d, время доступа к памяти (DRAM) в тактах ядра процессора: %d\n", (void *)(&t_arr[adr]), adr, t_arr[adr], t2 - t1);		
		//printf("%p => adr[%u] = %d, время доступа к памяти (DRAM) в тактах ядра процессора: %d\n", (void *)(&t_arr[adr]), adr, R, t2 - t1);		
	}

	printf("\nПри чтении одного байта кэшируется страница памяти.\n");	
	// Чтение из кэша.
	adr = m_adr[K-1] + 0x1000 - 1;
	t1 = __rdtsc();
	t_arr[adr] = 101;
	t2 = __rdtsc();
	printf("%p => adr[%u] = %d, время доступа к памяти (DRAM) в тактах ядра процессора: %d\n", (void *)(&t_arr[adr]), adr, t_arr[adr], t2 - t1);

	// Чтение НЕ из кэша.
	adr = m_adr[K-1] + 0x1000;
	t1 = __rdtsc();
	t_arr[adr] = 102;
	t2 = __rdtsc();
	printf("%p => adr[%u] = %d, время доступа к памяти (DRAM) в тактах ядра процессора: %d\n", (void *)(&t_arr[adr]), adr, t_arr[adr], t2 - t1);
	
	return 0;
}
