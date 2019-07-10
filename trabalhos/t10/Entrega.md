lokijuhygb

ELC139 Programação Paralela

# T10: 

Comparativo entre [OpenMP](https://www.openmp.org/) e [TBB (Threading Building Blocks)](https://www.threadingbuildingblocks.org/) utilizando `#pragma simd` e o problema `Mandelbrot` no node [CDER03](https://help.rs.gsu.edu/display/PD/CDER).

[mandelbrot_serial.cpp](mandelbrot_serial.cpp)

[mandelbrot_openmp.cpp](mandelbrot_openmp.cpp)

[mandelbrot_openmp_simd.cpp](mandelbrot_openmp_simd.cpp)

[mandelbrot_tbb.cpp](mandelbrot_tbb.cpp)

[mandelbrot_tbb_simd.cpp](mandelbrot_tbb_simd.cpp)

[resultados.ods](resultados.ods)


<img src="speedup1.png" width="600">
<img src="speedup2.png" width="600">
<img src="speedup3.png" width="600">

<img src="efficiency1.png" width="600">
<img src="efficiency2.png" width="600">
<img src="efficiency3.png" width="600">


## Referências

https://pdfs.semanticscholar.org/7b80/cc9d5e00567f7f509b18dc33f66935ab4b7f.pdf

https://en.wikipedia.org/wiki/Threading_Building_Blocks

https://software.intel.com/en-us/articles/migrate-your-application-to-use-openmp-or-intelr-tbb-instead-of-intelr-cilktm-plus

https://software.intel.com/en-us/advisor

http://www.inf.ufrgs.br/erad2018/downloads/minicursos/eradrs2018-openmp.pdf

https://www.ibm.com/support/knowledgecenter/en/SSXVZZ_16.1.1/com.ibm.xlcpp1611.lelinux.doc/compiler_ref/prag_omp_simd.html

http://hpac.rwth-aachen.de/teaching/pp-16/material/08.OpenMP-4.pdf

https://www.threadingbuildingblocks.org/docs/help/reference/appendices/community_preview_features/tbb_global_control.htm

ftp://ftp.inf.ufrgs.br/pub/geyer/PDP-CIC-ECP/slidesAlunos/AulaExtra-2011-1/PDP-2011-1-tbb-Stefano.pdf

https://software.intel.com/pt-br/articles/programacao-vetorial-e-paralela-com-amplificador-intel-vtune

https://computing.llnl.gov/tutorials/linux_clusters/intelAVXperformanceWhitePaper.pdf

http://www.doc.ic.ac.uk/~dt10/teaching/2011/hpce/hpce-lec7-tbb-details.pdf

https://bps90.github.io/assets/files/2012-03-12-ERBASE_28-03-12_versao_submetida.pdf
