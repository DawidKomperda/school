# Zadanie 7 - Rozkład normalny (krzywa dzwonowa)

print("Generowanie 10 000 normalnie rozłożonych wartości...")
E1_2 <- rnorm(10000)

print("Tworzenie histogramu rozkładu normalnego...")
hist(E1_2, col = 'red')

