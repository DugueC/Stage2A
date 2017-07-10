#
#  Expect the name of the parameters file
#

if [ $# -eq 1 ]
  then
    ./sim_areaint.exe $1
    R CMD BATCH '--args '$1 ../R/Rscript.R ../R/Rscript.out

  else
    echo "Usage : write the name of the parameters file"
fi
