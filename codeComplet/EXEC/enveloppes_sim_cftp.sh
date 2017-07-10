#
#  Expect the name of the parameters file
#

if [ $# -eq 1 ]
  then
    ./sim_cftp.exe $1
    #R CMD BATCH '--args ../PARAMS/p_str_cftp_A.txt' ../R/Rscript.R ../R/Rscript.out
    R CMD BATCH '--args '$1 ../R/Rscript.R ../R/Rscript.out

  else
    echo "Usage : write the name of the parameters file"
fi
