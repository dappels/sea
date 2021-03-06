#!/bin/sh
# plot.sh <file(s)>
#	Plot CSV files generated by Sealib RuntimeTest.

ScriptHome=$(dirname $(readlink -e "$0"))

Title="Runtime test"
Files=""
Outfile="runtime-plot.jpg"
Scale="ms"
Ratio=F

printHelp() {
	printf "plot.sh [options] <file basename(s)>\n"
	printf "Options:\n"
	printf "\t-t <name>		Title for your plot\n"
	printf "\t-o <file>		Output filename (default: $Outfile)\n"
	printf "\t-s <unit>		Unit of time measure (default: $Scale)\n"
	printf "\t-r			Enable ratio plotting of two data files\n"
	printf "\n"
	printf "Example:\nPlot data from standard.csv and efficient.csv in one plot\n"
	printf " -> plot.sh -t 'Algorithm comparison' -o comparison.jpg standard efficient\n"
	exit 0
}
if test $# -eq 0; then
	printHelp
fi

while getopts "t:o:s:rh" opt; do
	case $opt in
	t) 
		Title="$OPTARG" 
		printf "Title: $Title\n"
		;;
	o)
		Outfile="$OPTARG"
		;;
	s)
		Scale="$OPTARG"
		;;
	r)
		Ratio=T 
		printf "Ratio: yes\n"
		;;
	h|?)
		printHelp
		;;
	esac
done
shift $((OPTIND-1))

printf "Output file: $Outfile\n"

if test $Ratio = F; then
	for file in "$@"; do
		Files="$Files$file "
	done
	printf "Plotting files: $Files\n"
	gnuplot -e "infiles='$Files'; outfile='$Outfile'; title='$Title'; scale='$Scale'" -c "$ScriptHome/plot_helper.gp"
else
	printf "Plotting ratio: $1 / $2\n"
	gnuplot -e "infile1='$1'; infile2='$2'; outfile='$Outfile'; title='$Title'; ratio='yes'" -c "$ScriptHome/plot_helper.gp"
fi
