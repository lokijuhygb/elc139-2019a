#!/bin/sh

# compila os programas parte 1
smpicc -o sr_bcast sr_bcast.c
smpicc -o b_bcast  b_bcast.c

# executa 10 testes para cada quantidade de processos e para cada programa
for i in sr_bcast b_bcast
do
	for j in `seq 2 4 128`
	do
		# executa 10 vezes
		for k in $(seq 1 1 10)
		do
			start=`date +%s.%N`
				smpirun -np $k -hostfile cluster_hostfile.txt -platform cluster_crossbar.xml ./$i --cfg=smpi/host-speed:10000000
			end=`date +%s.%N`

			runtime=$( echo "$end - $start" | bc -l | cut -d"." -f2)

			echo $i,$j,$k,$runtime >> resultados_parte1.csv
		done
	done
done

# compila o programa parte 2
smpicc -o avg avg.c

# varia a velocidade
for i in 125 250
do
	sed -e 's/\(bw=\"\)[0-9]*\(Mbps\"\)/\1'$i'\2/' cluster_crossbar.xml > aaabbb
	mv aaabbb cluster_crossbar.xml
	
	# varia a latencia
	for j in `seq 5 5 15`
	do
		sed 's/\(lat=\"\)[0-9]*\(us\"\)/\1'$j'\2/' cluster_crossbar.xml > aaabbb
		mv aaabbb cluster_crossbar.xml

		# varia o tamanho do vetor
		for k in 100 1000 3000
		do
			# varia a quantidade de processos
			for m in 1 2 4 8 16 32 64 128
			do
				# executa 10 vezes
				for l in $(seq 1 1 10)
				do
					start=`date +%s.%N`
						smpirun -np $m -hostfile cluster_hostfile.txt -platform cluster_crossbar.xml ./avg $k --cfg=smpi/host-speed:10000000
					end=`date +%s.%N`

					runtime=$( echo "$end - $start" | bc -l )

					echo $i,$j,$k,$m,$runtime >> resultados_parte2.csv
				done
			done
		done
	done
done

# https://unix.stackexchange.com/questions/52313/how-to-get-execution-time-of-a-script-effectively
