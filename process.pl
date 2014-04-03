
#$main_genre = 'classical';
#$feature = "ZCR";


sub calculateAndWrite{
	my ($file_examples, $file_test ,$dir_path, $target, $exaples_size, $test_size, $feature) = @_;

	opendir (DIR,$dir_path);

	my $i = 0;
	my $test_i = 0;
	my $exmp_i = 0;
	my $index;
	my @dir_files = readdir(DIR);
	$dir_files_size = @dir_files;
	while (1){
		$index = int(rand($dir_files_size));
		$cur_file = $dir_files[$index];
		splice(@dir_files,$index,1);
		$dir_files_size -= 1;
		if($dir_files_size == 0){
			last;
		}
		if($cur_file =~/.wav/){
			my $res = `./music_classifier-release-build/music_classifier $dir_path"/"$cur_file $feature`;
		    #my $res = `./music_classifier-release-build/music_classifier $dir_path"/"$cur_file $i`;
			print $i," ",$cur_file," ",$target," ";
			if(($i % 2) == 1){
				if($exmp_i < $exaples_size){
					#print "examples\n";
					print $file_examples $target." ".$res."\n";
					$exmp_i++;
				}
				else{
					if($test_i < $test_size){
						#print "test\n";
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
						#print "test\n";
				  		print $file_test $target." ".$res."\n";
				  		$test_i++;
					}
				
				else{
					if($exmp_i < $exaples_size){
						#print "examples\n";
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

sub perform{

my ($main_genre,@features) = @_;

	$feature = join(" ",@features);
	$path_feature = join("_",@features);

	$exapmles_main_size = 72;
	$exapmles_sub_size = 12; 

	$test_main_size = 24;
	$test_sub_size = 4;



	$test_file_name = "test_".$main_genre;
	$examples_file_name = "examples_".$main_genre;


	#@genre_list = ("classical","reggae","blues","rock","jazz","country","disco","hiphop","metal","pop");
	@genre_list = ("reggae","blues","rock","jazz","country","disco","hiphop");
	#@genre_list = ("metal","rock");
	#@genre_list = ("jazz","blues");

	if (! -d "./data/".$main_genre){
		mkdir("./data/".$main_genre);
	}

	if(! -d "./data/".$main_genre."/".$path_feature){
		mkdir("./data/".$main_genre."/".$path_feature);
	}

	my $examples_path = "./data/".$main_genre."/".$path_feature."/".$examples_file_name.".txt";
	my $test_path = "./data/".$main_genre."/".$path_feature."/".$test_file_name.".txt";
	my $model_name = "./data/".$main_genre."/".$path_feature."/"."model_".$main_genre."_".$feature.".txt";

	open(Fexmp, ">", $examples_path) or die "Ошибка открытия файла:  $!";
	open(Ftest, ">", $test_path) or die "Ошибка открытия файла:  $!";

	for my $genre (@genre_list){
		
		$dir_path = "./data/dataset/".$genre."_wav";

		if($genre eq $main_genre){
			calculateAndWrite(Fexmp,Ftest,$dir_path,1,$exapmles_main_size,$test_main_size,$feature);
		} else {
			calculateAndWrite(Fexmp,Ftest,$dir_path,-1,$exapmles_sub_size,$test_sub_size,$feature);
		}

	    
		
		
	}
	close(Fexmp);
	close(Ftest);

	if (! -e "./data/".$main_genre."/".$main_genre."_result.txt"){
		open(Fresult,">","./data/".$main_genre."/".$main_genre."_result.txt");
	}
	else{
		open(Fresult,">>","./data/".$main_genre."/".$main_genre."_result.txt");
	}

	for (my $i = 0; $i < 3; $i++){
		`./data/svm_learn -t $i $examples_path $model_name`;
		my @examples_classify = reverse(split('\n',`./data/svm_classify $examples_path $model_name`));
		my @test_classify =  reverse(split('\n',`./data/svm_classify $test_path $model_name`));
		print Fresult $feature." kernel ".$i.":\n";
		print Fresult "examples: ".@examples_classify[1]."\n";
		print Fresult "test: ".@test_classify[1]."\n\n";
	}
	close(Fresult);

}

my ($genre,$feature)  = @ARGV ;
#perform("rock",("MFCC","ZCR","BEATHISTO","PITCHHISTO"));
perform($genre,($feature));

