
$style = "blues";
$dir_path = "./data/dataset/".$style."_wav";
open(F1, ">", "./data/".$style.".dat") or die "Ошибка открытия файла:  $!";
opendir (DIR,$dir_path);
my $i = 0;

foreach my $cur_file (readdir(DIR)){
	if($cur_file =~/.wav/){
	print $i,"\n";
	my $res = `./music_classifier-build/music_classifier $dir_path"/"$cur_file`;
	print $res,"\n";
	print F1 $res;
	$i++;
	}
}
closedir (DIR);
