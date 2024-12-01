set terminal pngcairo size 1920,1080 enhanced
set output 'histogram.png'
set title 'Weekly Sales Histogram of supplier t88'
set xlabel 'Days of the Week'
set ylabel 'Quantities'
set grid
set style data histograms
set style fill solid border -1
set boxwidth 0.6
set style line 1 lc rgb 'blue' pt 7 ps 1.5 lw 2
plot 'data.txt' using 2:xtic(1) title 'Quantities' ls 1
