library(rgl)
t <- read.table("./music_classifier-build/out.txt")
x <- unlist(t[][1])
y <- unlist(t[][2])
z <- unlist(t[][3])
m <- max(z)
z <- z/m
z <- sqrt(z)

plot3d(x,y,z,col="blue",size=2)