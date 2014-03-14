t <- read.table("./music_classifier-build/out.txt")
x <- unlist(t[][1])
y <- unlist(t[][2])
plot(x,y,'l',cex=0.01)