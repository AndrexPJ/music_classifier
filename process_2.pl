#@genre_list = ("pop","jazz","reggae","metal"); 
#@genre_list = ("classical","reggae","blues","rock","jazz","country","disco","hiphop","metal","pop"); 
@genre_list = ("classical","reggae","blues","rock","jazz","country","disco","hiphop","metal","pop"); 
@feature_list = ("PITCHHISTO","MFCC","BEATHISTO","ENERGY","ZCR","SPCENTROID","SPROLLOFF","SPFLATNESS","SPFLUX");
#@feature_list = ("ZCR");
foreach my $genre (@genre_list){
	foreach my $feature (@feature_list){
		print $genre." ".$feature." begin...\n";
		`perl process.pl $genre $feature`;
		print $genre." ".$feature." end!\n";
	}
}

