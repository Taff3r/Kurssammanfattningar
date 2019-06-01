## Little's sats:
	E(N), i allmänhet, där k = antal köplatser + antal bejtänare

	E(N) = p1 + p2 + p3 + ... + pk	
	
	E(N) = Lambda, eff * E(T), Lambdaeff = antal kunder som kommer igenom systemet.

I med def. av Lambdaeff ovan, kan INTE Little's sats användas om en kund skulle hoppa av i systemet, ex. av att den skulle bli trött på att vänta i kön.

### Z-transformer:

Första deriveringen av Z-transformen är medelvärdet, där z => 1
Andra derivering av Z-transformen ger andramomentet, där z => 1

### Betjänade kunder / tid:

	E(Kund/tid) = Lamda, eff

### Snitt kunder i betjänare:

	E(N,s) = rho

### TIPS:

Little's sats kan också användas för att räkna ut hur lång tid det i snitt det spenderas i en buffert:
	
	Ex. 2 köplatser, 2 betjänare:
	E(N,b) = 1*p,3 + 2*p,4


	
# M/G/1-system:

### Kriterier:

1. Ankomsterna är en poissonprocess med intensitet Lambda som är konstant och inte beror på hur många kunder det finns i systemet. 
2. Det finns en betjänare och betjäningstiden har en godtycklig men känd fördelning.
3. Det finns en oändligt många buffertplatser.


### LaPlace-transformer:

Första deriveringen av LaPlacetransformen är medelvärdet, där s => 0.
Andra derivering av LaPlacetransformen ger andramomentet, där s => 0.

OBS! Ignorera om det blir negativt.
# Könät

### Snitt kunder i en nod:
	
	N,k = rho,k/(1-rho,k), rho,k = lambda,k / mu,k 

### Snitt tid spenderat i ett könät:

	T = (N1 + N2 + ... + Nk ) / Lambdatot

### Snitt tid spenderat i en nod i ett könät:

	E(T,k) = E(N,k) / Lambda, k (Little's sats)

### Tips:

När ett könät får väldigt stor input kan det vara bra att rita om systemet där de ytteresta noderna skrivs om som deras output. Om det inte finns en spärrr i de yttersta noderna.

# Loop-back system

Lös ut samtliga lambda i  ett ekvationssystem i termer av de originella lambda. 

	Ex.
	L1 = L + 0.8L2 + 0.5L3
	L2 = 0.5L1
	L3 = 0.5L2
	Ger:
	L1 = (20/7)L
	L2 = (10/7)L
	L3 = (10/7)L

### Sannolikheten att en kund lämnar i en specifik utgång från systemet (Ingen spärr):

	P(Lämnar genom X) = Genomströming genom X / Total genomströmning

### Antal besök i en nod k (Ingen spärr):
	
	E(Antal besök i k) = Lambda, k / Lambda, tot

Således blir:

	E(Antal betjäningar) = Sum, 1->k (Lambda, k/Lambda, tot)

### Total tid i medel spenderad i en nod k:
	
	(Lambda, k / Tot. Lambda in) * E(T,k) = E(T,k_tot)

### Medeltiden som en godt. kund spenderar i ett kösystem:
Medeltiden som en godt. kund spenderar i ett kösystem är medelbetjäningstiden multiplicerat med medelantalet gånger kunden passerar kösystemet.

### Medeltiden spenderat i en väg i ett könät:

	(Lambda, väg / Summan av samtliga möjlig vägar)* (E(T, första noden på vägen) + E(T, andra noden...) + ... ) = E(T, väg)
## Annat:
### Idleperiod:

	E(Idle) = 1/Ankomstintensitet i tillstånd 0 = 1/Lambda

### Medelantal kunder som blir betjänade per tidsenhet:
	
	Ex. Med två betjänare och två köplatser:
	E(Kunder/tid) = 2mu * (p2 + p3 + p4) + mu * p1

### Sannolikhet att en kund som inte spärras blir betjänad:

	Lambda,serv / Lambda,eff = P(Betjänad som inte blev spärrad)
	Där Lambda,serv = Summan av Total mu vid tillstånd vid alla tillstånd k där betjänare jobbar.
	
Ex. 2 betjänare, köplats, där båda har mu = 5
	Lambda, serv = 5p1 + 10p2 + 10p3

### Erlangsystem:

Ett Erlangsystem är ett system som endast består av betjänare.
Då är "betjänare" definerat som ett ställe där en kund kan komma ur systemet.
Ex. en kö som kunder kan lämna med samma intensitet som betjänaren/na kan modelleras som ett Erlangsystem.
