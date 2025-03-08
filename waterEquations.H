//Update Saturation Pressure
Info << "Updating Saturation pressures " << nl << endl;

pSaturationWater = 
pow(10, -7.90298*(fracT/T-1) 
+  5.02808 * log10(fracT/T)
- 1.3816e-7 * (pow(10,11.344*(1-T/fracT)) - 1)
+ 8.1328e-3 * (pow(10,-3.49149*(fracT/T-1) ) - 1) 
+ log10(dimensionedScalar(dimless,1013.246))) * dimensionedScalar("pressureFactor",dimPressure,100);

//Update Vapour Pressure

Info << "Updating Vapour Pressures" << nl << endl;

pVapour = rho * vapourH2O * RVapour * T;

//Update Saturation

Info << "Updating Saturations" << nl << endl;

satWater = pVapour / pSaturationWater;

