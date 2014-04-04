library(rgl)
t <- read.table("./music_classifier-build/out.txt")
x <- unlist(t[][1])
y <- unlist(t[][2])
z <- unlist(t[][3])
m <- max(abs(z))
z <- (z/m + 1) / 2
z <- sqrt(z)

plot3d(x,y,z,col="blue",size=2)