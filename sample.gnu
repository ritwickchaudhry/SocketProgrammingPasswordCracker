set term postscript eps color

set output 'plt.jpg'

#used to make the fonts appear larger;  makes the figure smaller but keeps the fonts same size
set size 0.6, 0.6
set key right bottom


set xlabel "Workers"
set ylabel "Time"

plot 'plot6.txt' using 2:1 t'6 Digits' with lines \
plot 'plot7.txt' using 2:1 t'7 Digits' with lines \
plot 'plot8.txt' using 2:1 t'8 Digits' with lines \

