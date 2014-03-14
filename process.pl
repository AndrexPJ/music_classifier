
$main_genre = 'jazz';

$exapmles_main_size = 70;
$exapmles_sub_size = 70; 

$test_main_size = 30;
$test_sub_size = 30;



$test_file_name = "test_".$main_genre;
$examples_file_name = "examples_".$main_genre;

#@genre_list = ("classical","reggae","blues","rock","jazz","country","disco","hiphop","metal","pop");
#@genre_list = ("metal","rock");
@genre_list = ("jazz","blues");

sub calculateAndWrite{
	my ($file_examples, $file_test ,$dir_path, $target, $exaples_size, $test_size) = @_;

	opendir (DIR,$dir_path);

	my $i = 0;
	my $test_i = 0;
	my $exmp_i = 0;

	foreach my $cur_file (readdir(DIR)){

		if($cur_file =~/.wav/){
			my $res = `./music_classifier-release-build/music_classifier $dir_path"/"$cur_file `;
		    #my $res = `./music_classifier-release-build/music_classifier $dir_path"/"$cur_file $i`;
			print $i," ",$cur_file," ",$target," ";
			if(($i % 2) == 1){
				if($exmp_i < $exaples_size){
					print "examples\n";
					print $file_examples $target." ".$res."\n";
					$exmp_i++;
				}
				else{
					if($test_i < $test_size){
						print "test\n";
				  		print $file_test $target." ".$res."\n";
				  		$test_i++;
					}
					else{
						last;
					}
				}
				
			}
			else{

				if($test_i < $test_size){
						print "test\n";
				  		print $file_test $target." ".$res."\n";
				  		$test_i++;
					}
				
				else{
					if($exmp_i < $exaples_size){
						print "examples\n";
						print $file_examples $target." ".$res."\n";
						$exmp_i++;
					}
					else{
						last;
					}
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



