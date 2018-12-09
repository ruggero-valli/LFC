binwidth=0.1
bin(x,width)=width*floor(x/width)

plot 'gauss_points.dat' using (bin($1,binwidth)):(1.0) smooth freq with boxes

#https://stackoverflow.com/questions/2471884/histogram-using-gnuplot
