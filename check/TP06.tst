[],
"Warning: some commands like subs might change arguments order",
0,0,0,1,0,1e-10,10,[1,50,0,25],0,0,0,
proc(A) 
  local n,i,j,P,L,M; 
  n:=(dim(A))[1];  
  P:=0;  
  L:=copy([seq(i,i=(0 .. n))]);  
  for i from 0 to n do  
  M:=1; 
  for j in L minus [i] do M:=M*(x-j)/(i-j); 
   od; 
  P:=P+det(i*identity(n)-A)*M; 
   od;  
  normal(P);  
 
end;,
"Done",
12,
"Done",
0,
"Done",
132,
"Done",
"Done",
poly1[1,-31,-2022,123635,-251766,-103090999,4182662387,-41451141688,-8022359112299,416152954730242,4177344029930032,-844396479840954874,24218768721172315816,391251849404736164524,-46549703110671685451500,1392577696358403748041340,5181017157107180520657627,-2643884145201343201568980663,109741771903208349344673461886,-175150709436626668118361574774,-117445953301049382229381718063738,3969525807197401486999224425277696,-44299562034492237546241987506524978,-1793777913030072566778742889603878877,124159323585122187902860026933655237731,-2800905964290210772630149457240035722124,-29475744993330987537788628575660087904419,3769930973039240282813482105020819361110746,-99422049472454281950204164582604568259119369,179859897620243884985696773720049191753752007,60589743994002952295818664939013728057098870333,-1745617909768309395960688915944987352733054851574,21103457414354678286283566718427029809626291202507,-45637860150265281055454591916339190934602873229297,-13056361725527582045804989160565012818991041744402880,211706123204191353423853257535853967909662138691925630,3331616526567075513504719091979873343545528955931512123,-134777615906931618685020730107460226975600318629603216003,3391864345546432921533807967677245891965008659740538607649,-52575540167721682809978326688131151045034422951025625468772,1919770751068671911307503080834529246856922198982863596575296,-27147088666252262751685484950928853174468263867112525335115342,-212407079935729071160135512583441209266227045604343899211014363,1597122667363216978471304860437125390341067267187020888076763035,-147791776785604135439394845053084405762004939693666641070838596922,3946448441571972815910277809464894624496283306668328446493973758410,-8876932284738157620851427899583834145111908294500394890189200738243,-478187379184690479777354838773611226168746865982719857160704017400664,3015446930679197542831693866898542713929656165675018260791625147339076,-6598890833260183615423396696644336875014320919956992266775727049551976,73585896952033432242293228404127739435373759392255315777210637517828244],
(((((((((((((((((((((((((((((((((((((((((((((((((x-31)*x-2022)*x+123635)*x-251766)*x-103090999)*x+4182662387)*x-41451141688)*x-8022359112299)*x+416152954730242)*x+4177344029930032)*x-844396479840954874)*x+24218768721172315816)*x+391251849404736164524)*x-46549703110671685451500)*x+1392577696358403748041340)*x+5181017157107180520657627)*x-2643884145201343201568980663)*x+109741771903208349344673461886)*x-175150709436626668118361574774)*x-117445953301049382229381718063738)*x+3969525807197401486999224425277696)*x-44299562034492237546241987506524978)*x-1793777913030072566778742889603878877)*x+124159323585122187902860026933655237731)*x-2800905964290210772630149457240035722124)*x-29475744993330987537788628575660087904419)*x+3769930973039240282813482105020819361110746)*x-99422049472454281950204164582604568259119369)*x+179859897620243884985696773720049191753752007)*x+60589743994002952295818664939013728057098870333)*x-1745617909768309395960688915944987352733054851574)*x+21103457414354678286283566718427029809626291202507)*x-45637860150265281055454591916339190934602873229297)*x-13056361725527582045804989160565012818991041744402880)*x+211706123204191353423853257535853967909662138691925630)*x+3331616526567075513504719091979873343545528955931512123)*x-134777615906931618685020730107460226975600318629603216003)*x+3391864345546432921533807967677245891965008659740538607649)*x-52575540167721682809978326688131151045034422951025625468772)*x+1919770751068671911307503080834529246856922198982863596575296)*x-27147088666252262751685484950928853174468263867112525335115342)*x-212407079935729071160135512583441209266227045604343899211014363)*x+1597122667363216978471304860437125390341067267187020888076763035)*x-147791776785604135439394845053084405762004939693666641070838596922)*x+3946448441571972815910277809464894624496283306668328446493973758410)*x-8876932284738157620851427899583834145111908294500394890189200738243)*x-478187379184690479777354838773611226168746865982719857160704017400664)*x+3015446930679197542831693866898542713929656165675018260791625147339076)*x-6598890833260183615423396696644336875014320919956992266775727049551976)*x+73585896952033432242293228404127739435373759392255315777210637517828244,
(((((((((((((((((((((((((((((((((((((((((((((((((x-74+2444)*(x-73)+2869672)*(x-72)+2156738407)*(x-71)+1166278023376)*(x-70)+483630901351987)*(x-69)+160061545540584124)*(x-68)+43447549150628166621)*(x-67)+9865012670793641976061)*(x-66)+1901518964861364472777994)*(x-65)+314723211781201362981491661)*(x-64)+45132305732056678049484731317)*(x-63)+5648095795572215702028325518670)*(x-62)+620439024703670319953595110820454)*(x-61)+60108314781265273344319136612522099)*(x-60)+5155673028744657384665029216853730553)*(x-59)+392751190857995535437354850063036237163)*(x-58)+26640173558314928879412250658969474513968)*(x-57)+1612238668563471265943190782548220953436656)*(x-56)+87194578117181159693258089215303674414538015)*(x-55)+4219358786561222224098191626540509387708325292)*(x-54)+182844686667762691762929250314921403649021156643)*(x-53)+7099831163063101735906052273004833705053130640956)*(x-52)+247101926944111190650872550896602591117957205432002)*(x-51)+7708894543819328327601821322195869365450213074489965)*(x-50)+215537987087942060008088157243692941972696435620142832)*(x-49)+5398965792164220702715381219178239473753995749335285238)*(x-48)+121091025019713299170464052539730875668008938267404490871)*(x-47)+2430063073365972242241600047903207853997968488137875638377)*(x-46)+43597198043482623892957288619707966540504428208417466134852)*(x-45)+698591373389661835136842965815870067847464079141682969644867)*(x-44)+9987985028662611538232858419713447288621114709528131415994249)*(x-43)+127291049677218276481570325940846940283314180130885097876231210)*(x-42)+1444812344067614118825955605198381805810287149751033390412627454)*(x-41)+14596940441758354507773150202029201517387561384183295226245003673)*(x-40)+131247188002841657145785544861296176203027924513693013369102954179)*(x-39)+1050837653620924074337431007689752737817623743864801201635627260786)*(x-38)+7503103551312311512842683080068446613477742847959442146291937437075)*(x-37)+47898241516635460166234147114258414337826625315340933380957607682584)*(x-36)+274360469040618121589266179564538723881944035206455175211408903031476)*(x-35)+1415794279292911822798593666453532508383283638800960840515619991267986)*(x-34)+6603573578613551924861718783648077786453069787459557394315786264453358)*(x-33)+27845954258045829105502190303565986430979466141991700784424490823092715)*(x-32)+105366815813186491186499937369087714555630350306168470577191404571409491)*(x-31)+348256695479059347258413464875103360249719987193839767879193288251055457)*(x-30)+928717890321672492502781155800895925337192414926080965922165110011261895)*(x-29)+1533566262699224031941911927554411251436752210367872691699510340870514482)*(x-28)-838576234932768755405048626997712982825528833517137182799941688282456255)*(x-27)-12673857443571570679225595549985135551992327505358454415585852588831351589)*(x-26)-29025570502040326690766975062807825204635099120914733142120268147262406028)*(x-25)-24668970068338847269398887048903905734087309479524944229210381666710048656,
x^50-31*x^49-2022*x^48+123635*x^47-251766*x^46-103090999*x^45+4182662387*x^44-41451141688*x^43-8022359112299*x^42+416152954730242*x^41+4177344029930032*x^40-844396479840954874*x^39+24218768721172315816*x^38+391251849404736164524*x^37-46549703110671685451500*x^36+1392577696358403748041340*x^35+5181017157107180520657627*x^34-2643884145201343201568980663*x^33+109741771903208349344673461886*x^32-175150709436626668118361574774*x^31-117445953301049382229381718063738*x^30+3969525807197401486999224425277696*x^29-44299562034492237546241987506524978*x^28-1793777913030072566778742889603878877*x^27+124159323585122187902860026933655237731*x^26-2800905964290210772630149457240035722124*x^25-29475744993330987537788628575660087904419*x^24+3769930973039240282813482105020819361110746*x^23-99422049472454281950204164582604568259119369*x^22+179859897620243884985696773720049191753752007*x^21+60589743994002952295818664939013728057098870333*x^20-1745617909768309395960688915944987352733054851574*x^19+21103457414354678286283566718427029809626291202507*x^18-45637860150265281055454591916339190934602873229297*x^17-13056361725527582045804989160565012818991041744402880*x^16+211706123204191353423853257535853967909662138691925630*x^15+3331616526567075513504719091979873343545528955931512123*x^14-134777615906931618685020730107460226975600318629603216003*x^13+3391864345546432921533807967677245891965008659740538607649*x^12-52575540167721682809978326688131151045034422951025625468772*x^11+1919770751068671911307503080834529246856922198982863596575296*x^10-27147088666252262751685484950928853174468263867112525335115342*x^9-212407079935729071160135512583441209266227045604343899211014363*x^8+1597122667363216978471304860437125390341067267187020888076763035*x^7-147791776785604135439394845053084405762004939693666641070838596922*x^6+3946448441571972815910277809464894624496283306668328446493973758410*x^5-8876932284738157620851427899583834145111908294500394890189200738243*x^4-478187379184690479777354838773611226168746865982719857160704017400664*x^3+3015446930679197542831693866898542713929656165675018260791625147339076*x^2-6598890833260183615423396696644336875014320919956992266775727049551976*x+73585896952033432242293228404127739435373759392255315777210637517828244,
0,
0,
[1,-31,-2022,123635,-251766,-103090999,4182662387,-41451141688,-8022359112299,416152954730242,4177344029930032,-844396479840954874,24218768721172315816,391251849404736164524,-46549703110671685451500,1392577696358403748041340,5181017157107180520657627,-2643884145201343201568980663,109741771903208349344673461886,-175150709436626668118361574774,-117445953301049382229381718063738,3969525807197401486999224425277696,-44299562034492237546241987506524978,-1793777913030072566778742889603878877,124159323585122187902860026933655237731,-2800905964290210772630149457240035722124,-29475744993330987537788628575660087904419,3769930973039240282813482105020819361110746,-99422049472454281950204164582604568259119369,179859897620243884985696773720049191753752007,60589743994002952295818664939013728057098870333,-1745617909768309395960688915944987352733054851574,21103457414354678286283566718427029809626291202507,-45637860150265281055454591916339190934602873229297,-13056361725527582045804989160565012818991041744402880,211706123204191353423853257535853967909662138691925630,3331616526567075513504719091979873343545528955931512123,-134777615906931618685020730107460226975600318629603216003,3391864345546432921533807967677245891965008659740538607649,-52575540167721682809978326688131151045034422951025625468772,1919770751068671911307503080834529246856922198982863596575296,-27147088666252262751685484950928853174468263867112525335115342,-212407079935729071160135512583441209266227045604343899211014363,1597122667363216978471304860437125390341067267187020888076763035,-147791776785604135439394845053084405762004939693666641070838596922,3946448441571972815910277809464894624496283306668328446493973758410,-8876932284738157620851427899583834145111908294500394890189200738243,-478187379184690479777354838773611226168746865982719857160704017400664,3015446930679197542831693866898542713929656165675018260791625147339076,-6598890833260183615423396696644336875014320919956992266775727049551976,73585896952033432242293228404127739435373759392255315777210637517828244],
x^50-31*x^49-2022*x^48+123635*x^47-251766*x^46-103090999*x^45+4182662387*x^44-41451141688*x^43-8022359112299*x^42+416152954730242*x^41+4177344029930032*x^40-844396479840954874*x^39+24218768721172315816*x^38+391251849404736164524*x^37-46549703110671685451500*x^36+1392577696358403748041340*x^35+5181017157107180520657627*x^34-2643884145201343201568980663*x^33+109741771903208349344673461886*x^32-175150709436626668118361574774*x^31-117445953301049382229381718063738*x^30+3969525807197401486999224425277696*x^29-44299562034492237546241987506524978*x^28-1793777913030072566778742889603878877*x^27+124159323585122187902860026933655237731*x^26-2800905964290210772630149457240035722124*x^25-29475744993330987537788628575660087904419*x^24+3769930973039240282813482105020819361110746*x^23-99422049472454281950204164582604568259119369*x^22+179859897620243884985696773720049191753752007*x^21+60589743994002952295818664939013728057098870333*x^20-1745617909768309395960688915944987352733054851574*x^19+21103457414354678286283566718427029809626291202507*x^18-45637860150265281055454591916339190934602873229297*x^17-13056361725527582045804989160565012818991041744402880*x^16+211706123204191353423853257535853967909662138691925630*x^15+3331616526567075513504719091979873343545528955931512123*x^14-134777615906931618685020730107460226975600318629603216003*x^13+3391864345546432921533807967677245891965008659740538607649*x^12-52575540167721682809978326688131151045034422951025625468772*x^11+1919770751068671911307503080834529246856922198982863596575296*x^10-27147088666252262751685484950928853174468263867112525335115342*x^9-212407079935729071160135512583441209266227045604343899211014363*x^8+1597122667363216978471304860437125390341067267187020888076763035*x^7-147791776785604135439394845053084405762004939693666641070838596922*x^6+3946448441571972815910277809464894624496283306668328446493973758410*x^5-8876932284738157620851427899583834145111908294500394890189200738243*x^4-478187379184690479777354838773611226168746865982719857160704017400664*x^3+3015446930679197542831693866898542713929656165675018260791625147339076*x^2-6598890833260183615423396696644336875014320919956992266775727049551976*x+73585896952033432242293228404127739435373759392255315777210637517828244,
"Done",
123,
"Done",
poly1[1,-3301/260,38296189/270400,41695522299/35152000,-3311748582867987/73116160000,1246154877566525689/2924646400000,-6866279263361099721687/9885304832000000,-381970607252686798423353477/10280717025280000000,38522205507378226222872681223/411228681011200000000,9107637538161836010942097798548427/2779905883635712000000000,-16455573902523222635705575444659912099/722775529745285120000000000,180030759003638143506097339494396900117391/751686550935096524800000000000,11145796550927593933475801278185749777654997/19543850324312509644800000000000,564765299722684802648603026919109869224036273291/50814010843212525076480000000000000,-31993892453111224852746562341884977352138458993572399/52846571276941026079539200000000000000,4498186204750239436933926383296178386504299491824722359/27480217064009333561360384000000000000000,453690568391295757170610153975854335714556038976744080082109/7144856436642426725953699840000000000000000,-337686205333204541821976419727644848250131808962005049910221071/928831336763515474373980979200000000000000000,1780893140502418333626924795188323428676688103663296430778607475803/482992295117028046674470109184000000000000000000,-23101374070223753664714468662412394047099346131104422396521977343978367/251155993460854584270724456775680000000000000000000,19821527347678378500567463565636835171927342842690327365493372498173190979/522404466398577535283106870093414400000000000000000000,189744627250239274336721926378857871317603654941314634122502842813627333563471/135825161263630159173607786224287744000000000000000000000,729592077723778442823402187847606139676860413973039933936682773359409312144227811/70629083857087682770276048836629626880000000000000000000000,-38224036179413511833339352085300917928403179780464386043857730383012309966499329581/1836356180284279752027177269752370298880000000000000000000000,1603120468440164237796145025470417371149517926188292208148475473724678724695210972548233/1193631517184781838817665225339040694272000000000000000000000000,8183370914231065196184960294447613515769973243103643078676658714056659820536333925366532633/1241376777872173112370371834352602322042880000000000000000000000000,241052062702930568675781092372075016606786332676747843573452505620926107709081777209545240993/161378981123382504608148338465838301865574400000000000000000000000000,5633497648528570028036355727500929984616340932951814187172032549834449288821558270898224165359933/20979267546039725599059284000558979242524672000000000000000000000000000,-6500025586526479277683142140337643271472600448377487158183247582917255274762635646449907796577062081/2727304780985164327877706920072667301528207360000000000000000000000000000,7000401080728793588216154889317803267727098907841369379586365617832289543939748345632885632494177157427/709099243056142725248203799218893498397333913600000000000000000000000000000,-27410450002428114167806982890713355457815923102161969900941366171844849834799704453552054314807560924579/56727939444491418019856303937511479871786713088000000000000000000000000000000],
poly1[1,-3301/260,38296189/270400,41695522299/35152000,-3311748582867987/73116160000,1246154877566525689/2924646400000,-6866279263361099721687/9885304832000000,-381970607252686798423353477/10280717025280000000,38522205507378226222872681223/411228681011200000000,9107637538161836010942097798548427/2779905883635712000000000,-16455573902523222635705575444659912099/722775529745285120000000000,180030759003638143506097339494396900117391/751686550935096524800000000000,11145796550927593933475801278185749777654997/19543850324312509644800000000000,564765299722684802648603026919109869224036273291/50814010843212525076480000000000000,-31993892453111224852746562341884977352138458993572399/52846571276941026079539200000000000000,4498186204750239436933926383296178386504299491824722359/27480217064009333561360384000000000000000,453690568391295757170610153975854335714556038976744080082109/7144856436642426725953699840000000000000000,-337686205333204541821976419727644848250131808962005049910221071/928831336763515474373980979200000000000000000,1780893140502418333626924795188323428676688103663296430778607475803/482992295117028046674470109184000000000000000000,-23101374070223753664714468662412394047099346131104422396521977343978367/251155993460854584270724456775680000000000000000000,19821527347678378500567463565636835171927342842690327365493372498173190979/522404466398577535283106870093414400000000000000000000,189744627250239274336721926378857871317603654941314634122502842813627333563471/135825161263630159173607786224287744000000000000000000000,729592077723778442823402187847606139676860413973039933936682773359409312144227811/70629083857087682770276048836629626880000000000000000000000,-38224036179413511833339352085300917928403179780464386043857730383012309966499329581/1836356180284279752027177269752370298880000000000000000000000,1603120468440164237796145025470417371149517926188292208148475473724678724695210972548233/1193631517184781838817665225339040694272000000000000000000000000,8183370914231065196184960294447613515769973243103643078676658714056659820536333925366532633/1241376777872173112370371834352602322042880000000000000000000000000,241052062702930568675781092372075016606786332676747843573452505620926107709081777209545240993/161378981123382504608148338465838301865574400000000000000000000000000,5633497648528570028036355727500929984616340932951814187172032549834449288821558270898224165359933/20979267546039725599059284000558979242524672000000000000000000000000000,-6500025586526479277683142140337643271472600448377487158183247582917255274762635646449907796577062081/2727304780985164327877706920072667301528207360000000000000000000000000000,7000401080728793588216154889317803267727098907841369379586365617832289543939748345632885632494177157427/709099243056142725248203799218893498397333913600000000000000000000000000000,-27410450002428114167806982890713355457815923102161969900941366171844849834799704453552054314807560924579/56727939444491418019856303937511479871786713088000000000000000000000000000000],
[1,2,3,4,5,6,7,8],
((((((x+2)*x+3)*x+4)*x+5)*x+6)*x+7)*x+8,
[8,7,6,5,4,3,2,1],
x^2+1,
[1,0,1],
3,
3,
sqrt(2)*sqrt(2)+1,
"Done",
8,
[1,2,3,4,5,6,7,8],
matrix[[-3,2,-4,4,-10,-9,8,2],[-5,3,-3,-5,3,-5,0,-4],[-10,9,-9,5,9,-2,4,0],[-2,5,-7,8,-10,9,9,-3],[-6,7,8,5,-1,0,-4,-6],[-4,6,-6,-6,-5,8,6,-9],[-9,-6,6,-2,2,-7,-4,8],[-5,-4,7,1,-2,7,-9,2]],
[1,2,3,4,5,6,7,8],
[1,2,3,4,5,6,7,8],
[1,2,3,4,5,6,7,8],[-27,-75,62,62,-29,-41,-7,-3],[528,-456,-860,-392,518,-1284,1174,759],[16662,5470,8322,-8899,-24968,-9985,5008,-26300],[219079,32850,-421493,148367,123135,281342,-325521,-173466],[-5026625,-817642,1883579,2754916,-1494888,2202669,-6803271,277002],[-41817366,-13351135,-5342573,-12468229,80325428,-30847174,66957760,124535564],[329350698,144472187,1336209697,-897334462,-1043005330,-1173450582,1554378670,-517504656],[22757844230,4072961834,-19328449006,-1057563976,3168724973,6727414838,1751529188,-14921069577],
[76463112,-13325458,1786523,-278347,39623,-2205,-118,4,-1],
(((((((-x+4)*x-118)*x-2205)*x+39623)*x-278347)*x+1786523)*x-13325458)*x+76463112,
matrix[[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0]],
[[0,0,0,1,0,0,0,0],[1,0,0,0,0,0,0,0],[0,1,0,0,0,0,0,0],[0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,-1],[0,0,0,0,1,0,0,0],[0,0,0,0,0,1,0,2],[0,0,0,0,0,0,1,0]],
[1,2,3,4,5,6,7,8],
[1,2,3,4,5,6,7,8],
[1,2,3,4,5,6,7,8],[4,1,2,3,-8,5,22,7],[3,4,1,2,-7,-8,19,22],[2,3,4,1,-22,-7,36,19],[1,2,3,4,-19,-22,31,36],[4,1,2,3,-36,-19,50,31],[3,4,1,2,-31,-36,43,50],[2,3,4,1,-50,-31,64,43],[1,2,3,4,-43,-50,55,64],
[[9/5,4/5,9/5,4/5,-1,0,-1,0],[4/5,9/5,4/5,9/5,0,-1,0,-1]],
[-1,0,1,0,1,0,-1,0,0],
((-x*x+1)*x*x+1)*x*x-1,
matrix[[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0]]
