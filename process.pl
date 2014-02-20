
$style = "classical";
$target = -1;
$dir_path = "./data/dataset/".$style."_wav";
open(F1, ">>", "./data/test_blues.txt") or die "Ошибка открытия файла:  $!";
opendir (DIR,$dir_path);
my $i = 0;
my $stop = 80;

foreach my $cur_file (readdir(DIR)){
	if($cur_file =~/.wav/){
	if($i < $stop){
		$i++;
		next;
	}
	print $i," ";
	my $res = `./music_classifier-build/music_classifier $dir_path"/"$cur_file`;
	print $res," ",$cur_file,"\n";
	print F1 $target." ".$res;
	$i++;
	#if($i == $stop){
	#	last;
	#}
	}
}
closedir (DIR);
