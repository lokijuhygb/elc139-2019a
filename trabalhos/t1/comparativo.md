[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > T1

TOP500 & me: Comparativo de Arquiteturas Paralelas
--------------------------------------------------

Nome: lokijuhygb

| Característica                                            | Computador no TOP500  | Meu computador  |
| --------------------------------------------------------- | --------------------- | --------------- |
| Nome/Título                                               | Sunway TaihuLight     | Lenovo ThinkPad X200 |
| Imagem (foto, diagrama, screenshot, etc.)                 | <img src="https://6lli539m39y3hpkelqsm3c2fg-wpengine.netdna-ssl.com/wp-content/uploads/2016/06/Sunway-TaihuLight-System-2016-768x343.png" width="200"> <img src="https://6lli539m39y3hpkelqsm3c2fg-wpengine.netdna-ssl.com/wp-content/uploads/2016/06/Sunway-TaihuLight-basic-layout-of-a-node.png" width="200"> | <img src="https://commons.wikimedia.org/wiki/File:Libreboot_on_Lenovo_Thinkpad_x200.jpg" width="200"> |
| Classificação de Flynn                                    | MIMD SIMD             | MIMD |
| Memória: compartilhada, distribuída ou ambas?             | Ambas                 | Compartilhada |
| Número total de núcleos de processamento                  | 10649600 (10485760 + 163840) (40960 nodes. 40 gabinetes x 4 supernodes x 256 nodes x 4 grupos de (8^2 cores + 1 core auxiliar)) | 2 (uma thread por core) |
| Fabricante e modelo do(s) processador(es)                 | Sunway SW26010        | Intel Core 2 Duo P8600 |
| Frequência do(s) processador(es)                          | 1.45 GHz              | 2.40 GHz |
| Memória total                                             | 1.31 PB DDR3 (32GB por node, 8GB para cada 8^2 cores) | 8GB DDR3 1333 MHz |
| Tipo(s) de interconexão entre os núcleos/processadores    | PCI-Express 3.0, NoC  | Bus |
| Desempenho Linpack                                        | 93 Pflop/s            | 5.517 Gflop/s  (Pacote HPCC) |
| Sistema Operacional                                       | Sunway RaiseOS 2.0.5  | Debian GNU/Linux-libre 9.8 (Stretch) |

### Referências
- [China Debuts 93-Petaflops ‘Sunway’ with Homegrown Processors](https://www.hpcwire.com/2016/06/19/china-125-petaflops-sunway/)
- [China's secretive super-fast chip powers the world's fastest computer](https://www.cio.com/article/3086104/chinas-secretive-super-fast-chip-powers-the-worlds-fastest-computer.html)
- [Intel® Core™2 Duo Processor P8600](https://ark.intel.com/content/www/us/en/ark/products/35568/intel-core-2-duo-processor-p8600-3m-cache-2-40-ghz-1066-mhz-fsb.html)
- [Now China outguns US in top supercomputer showdown](https://www.zdnet.com/article/now-china-outguns-us-in-top-supercomputer-showdown/)
- [Network on a chip](https://en.wikipedia.org/wiki/Network_on_a_chip)
- [Sunway (processor)](https://en.wikipedia.org/wiki/Sunway_(processor))
- [Sunway SW26010](https://en.wikipedia.org/wiki/Sunway_SW26010)
- [Sunway TaihuLight](https://en.wikipedia.org/wiki/Sunway_TaihuLight)
- [Supercomputing in China](https://en.wikipedia.org/wiki/Supercomputing_in_China)
- [Wikimedia Commons Category:ThinkPad X series](https://commons.wikimedia.org/wiki/Category:ThinkPad_X_series)
- [Top500 Sunway TaihuLight](https://top500.org/system/178764)
- [High Performance Computing Challenge](http://icl.cs.utk.edu/hpcc/)
- [HPC Challenge Benchmark](https://en.wikipedia.org/wiki/HPC_Challenge_Benchmark)
- [Where can I find missed hpccinf.txt for hpcc?](https://askubuntu.com/questions/1052180/where-can-i-find-missed-hpccinf-txt-for-hpcc)
- [Flynn's taxonomy](https://en.wikipedia.org/wiki/Flynn%27s_taxonomy)
- [GNU Linux-libre project](https://www.fsfla.org/ikiwiki/selibre/linux-libre/)
