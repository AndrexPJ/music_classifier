#@genre_list = ("classical","reggae","blues","rock","jazz","country","disco","hiphop","metal","pop"); 
@genre_list = ("disco"); #  jazz disco sprolloff
@feature_list = ("PITCHHISTO","MFCC");
foreach my $genre (@genre_list){
	foreach my $feature (@feature_list){
		print $genre." ".$feature." begin...\n";
		`perl process.pl $genre $feature`;
		print $genre." ".$feature." end!\n";
	}
}

