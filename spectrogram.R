t <- read.table("./music_classifier-build/out.txt")
x <- unlist(t[][1])
y <- unlist(t[][2])
z <- unlist(t[][3])
m <- max(z)
z <- z/m
z <- sqrt(z)

plot(x,y,'p',cex=0.3, col=rgb(1-z,1-z,1-z))