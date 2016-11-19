# TODO

- Valgrind 


- Bonus
-----------------------------------------------------------------------------------------------------

- 3.1 Lite klurig, men typ "go" ska mappas mot en plats i std::map som har pekare till en funktion?
- 3.2 Spara, skriv ner allting som är kvar till en fil och sedan läs in från den
- 3.3 Som ovan, men nu sparar man kartor, deras connectiong och objekt också (ALLT)
- 3.4 Här skapar man objekt som skapas och dör under spelets gång, shared_ptr och weak_ptr används
när man skickar med en pekare, t.ex. skapar en Skeleton sen slumpar i vilket rum den ska läggas in och då behövs 
shared_ptr antar jag för att inte läcka minne

-------------------------------------------------------------------------------------------------------

- Lyckades uppleva en bugg med Gold när jag dödade draken, men senare när jag testade igen var det bra
lägg märke till det när du testar, alltså det blev såhär i min inventory:
Misc: 12 Gold
: 10 Gold
Så ska det inte vara! Men hoppas det var något tillfälligt bara

- Kolla ifall buggen är kvar med off by one!!!
- 




# Frågor

 Q: Hur sker minnesallokeringen? Var görs allokering och destruktion?
 
 A: Allokerar all minne i main. delete och onExit samt när mobb dör destruktar.
 
 Q:Hur ser slingan ut som hanterar händelser. Hur hanteras händelser?
 
 A: I main har vi en slinga. Splitar input på mellanslag. Kollar kommandon. Händelser hanteras via pekare till medlemsfunktioner
 
 Q: Vad är det som håller reda på var spelaren är? Vad håller reda på alla
andra objekt i spelet? Hur ser det ut i minnet, visa en minnesbild.

A: Spelarn start i lobby, som är en Environment pekare. Därefter, när spelaren rör sig, ändras denna pekare, och pekar således på det rummet spelaren befinner sig i. I main har vi en lista med alla rum, där rummen håller reda på alla aktörer och items som finns.

Q: Hur kopplas miljöerna ihop? Visa minnesbild.

A: Rummen kopplas ihop med varandra. Alla rum har antingen norr, syd, öst eller väst grannar.

Q: Hur hittar man saker/grannar? Hur sker uppslagningen?

A: Om spelaren är i ett rum med items, vet rummet om det och visar den listan för spelaren. Vi använder std::vector för det.

Q: På vilket sätt skiljer sig karaktärer i spelet?

A: Alla karaktärer har saker gemensamt, ex. liv, damage, defence osv. Men en player ska troligtvis ha mer i liv och göra mer skada. Sen har vi andra karaktärer, exempelvis Humans och Creatures, missar olika ofta. Human missar oftare än Dragon. Och under kategorin Human har vi olika klasser som ropar olika saker när de slåss. En Warrior säger en sak med en Wizard något annat.

Q: Hur sker inmatning? Hur sker parsningen av det som inmatas?

A: Via terminalen.

Q: Hur fungerar action-metoden?

A: Spelaren har ingen action metod utan i main kollar vi vad spelaren vill göra. Alla fiender agerar när de stötar på spelaren. Det är då de slår honom.
 
 
