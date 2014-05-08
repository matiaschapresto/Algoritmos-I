#8 problemas
problemas = {};
problemas{end+1} = "calcularCuenta";
problemas{end+1} = "desRegistrarHuesped";
problemas{end+1} = "huespedesConPalabra";
problemas{end+1} = "registrarHuesped";
problemas{end+1} = "reservasSolapadas";
problemas{end+1} = "sobreReservado";
problemas{end+1} = "cadenasAmarretas";
problemas{end+1} = "fusionAutorizada";

#5 invariantes
invariantes = {};
invariantes{end+1} = "sinNombresRepetidosEnCadenas(inv)";
invariantes{end+1} = "estanAlMenosUnDia(inv)";
invariantes{end+1} = "siSeVaEntro(inv)";
invariantes{end+1} = "cadenasBienFormadas(inv)";
invariantes{end+1} = "hotelesConsistentes(inv)";

#me agrego los dos que empecé
problemasA = {};
	problemasA{end+1} = "pretencionesDePopStar";
problemasB = {};
problemasC = {};
problemasD = {};

invariantesA = {};
	invariantesA{end+1} = "noEntranDosVeces(inv)";
invariantesB = {};
invariantesC = {};
invariantesD = {};

p = randperm(8);
i = randperm(5);

problemasA{end+1} = problemas{p(1)};
problemasB{end+1} = problemas{p(2)};
problemasB{end+1} = problemas{p(3)};
problemasC{end+1} = problemas{p(4)};
problemasC{end+1} = problemas{p(5)};
problemasD{end+1} = problemas{p(6)};
problemasD{end+1} = problemas{p(7)};

invariantesB{end+1} = invariantes{i(1)};
invariantesC{end+1} = invariantes{i(2)};
invariantesD{end+1} = invariantes{i(3)};

pendientes = {};
pendientes{end+1} = problemas{p(8)};
pendientes{end+1} = invariantes{i(4)};
pendientes{end+1} = invariantes{i(5)};

disp("Emo");
disp([problemasA invariantesA]);

disp("Silvio");
disp([problemasB invariantesB]);

disp("Mati");
disp([problemasC invariantesC]);

disp("Alan??");
disp([problemasD invariantesD]);

disp("Problemas pendientes");
disp(pendientes);
