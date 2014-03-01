
$main_genre = 'metal';

$exapmles_main_size = 50;
$exapmles_sub_size = 50; 

$test_main_size = 0;
$test_sub_size = 0;



$test_file_name = "test_".$main_genre;
$examples_file_name = "examples_".$main_genre;

#@genre_list = ("classical","reggae","blues","rock","jazz","country","disco","hiphop","metal","pop");
@genre_list = ("metal","rock");
#@genre_list = ("jazz","blues");

sub calculateAndWrite{
	my ($file_examples, $file_test ,$dir_path, $target, $exaples_size, $test_size) = @_;

	opendir (DIR,$dir_path);

	my $i = 0;
	foreach my $cur_file (readdir(DIR)){

		if($cur_file =~/.wav/){
			my $res = `./music_classifier-release-build/music_classifier $dir_path"/"$cur_file`;

			print $i," ",$cur_file,"\n";
			
			if($i < $exaples_size){
				print $file_examples $target." ".$res."\n";
			}
			else{
				if($i < $exaples_size + $test_size){
				  print $file_test $target." ".$res."\n";
				}
				else{
					last;
				}
			}
			
			$i++;
		}
	}
	
	closedir (DIR);
}

open(Fexmp, ">", "./data/".$examples_file_name.".txt") or die "Ошибка открытия файла:  $!";
open(Ftest, ">", "./data/".$test_file_name.".txt") or die "Ошибка открытия файла:  $!";

for my $genre (@genre_list){
	
	$dir_path = "./data/dataset/".$genre."_wav";

	if($genre eq $main_genre){
		calculateAndWrite(Fexmp,Ftest,$dir_path,1,$exapmles_main_size,$test_main_size);
	} else {
		calculateAndWrite(Fexmp,Ftest,$dir_path,-1,$exapmles_sub_size,$test_sub_size);
	}

    
	
	
}

close(Fexmp);
close(Ftest);



