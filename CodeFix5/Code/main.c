#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "../CHARGE/charge.h"
#include "../MEM/mem.h"
#include "../FUNCTIONS/functions.h"
#include "../PARAMETERS/read.h"
#include "../CHARGETRANSPORT/chargetransport.h"
#include "../CLUSTER/CLUSTERFUNCTIONS/clusterfunctions.h"
#include "../CLUSTER/CLUSTERSITENODE/clustersitenode.h"
#include "../CLUSTER/CLUSTERFUNCTIONS/SITENODE/sitenode.h"
#include "../CLUSTER/CLUSTERFUNCTIONS/MATRIX/matrix.h"
#include "../CLUSTER/CLUSTERFUNCTIONS/DATASTRUCT/cluster.h"

int main(void){

	//Program Timer
	time_t start;
	time_t finish;
	//double first;
	//double second;
	clock_t begin;
	clock_t end;
	double time_spent;
	begin = clock();
	time(&start);
	//first = CPU_TIME;

	srand(time(NULL));
						
	mem_init();
	//Constants
	//Boltzmann constant Units of [eV/K]
	static const double kB = 8.6173324E-5;
	//Planck constant Units of [eV s]
	static const double hbar = 6.58211928E-16;

	/*
	int PeriodicX;
	int PeriodicY;
	int PeriodicZ;

	int EndX;
	int EndY;
	int EndZ;

	int XElecOn;
	int YElecOn;
	int ZElecOn;
	*/
	/*
	double XFermiB;
	double XFermiF;
	double YFermiL;
	double YFermiR;
	double ZFermiB;
	double ZFermiA;

	double alphaxb;
	double alphaxf;
	double alphayl;
	double alphayr;
	double alphazb;
	double alphaza;
	*/

	/*
	double RelativePerm;
	
	double vX;
	double vY;
	double vZ;
	*/
	/*
	double D;
	int TCount;
	int NCh;
	int Ntot;
	double TStep;
	int N_av;
	int Nstep_av;
	*/
	/*
	double CutOff;
	double lambda;

	int SeedProt;
	int Attempts;
	
	double fracSeed;
	double E0;
	double sigma;

	double fracTrap;
	double Etrap;
	double Tsigma;
	*/
	int SLength;
	int SWidth;
	int SHeight;

	double VoltageX;
	double VoltageY;
	double VoltageZ;

	int VStepX;
	int VStepY;
	int VStepZ;

	double VincX;
	double VincY;
	double VincZ;

	double SiteDistance;
	
	int Rcount;

	double TempStart;
	int TemperatureStep;
	double TemperatureInc;
	double reOrgEnergy;
	double AttemptToHop;
	double gamma;

	ParameterFrame PF = newParamFrame();
	
	SLength = PFget_Len(PF);
	SWidth = PFget_Wid(PF);
	SHeight = PFget_Hei(PF);

	VoltageX = PFget_VoltageX(PF);
	VoltageY = PFget_VoltageY(PF);
	VoltageZ = PFget_VoltageZ(PF);

	VStepX = PFget_VStepX(PF);
	VStepY = PFget_VStepY(PF);
	VStepZ = PFget_VStepZ(PF);

	VincX = PFget_VincX(PF);
	VincY = PFget_VincY(PF);
	VincZ = PFget_VincZ(PF);

	SiteDistance = PFget_SiteDist(PF);

	Rcount = PFget_Rcount(PF);

	TempStart = PFget_TempStart(PF);
	TemperatureStep = PFget_TempStep(PF);
	TemperatureInc = PFget_TempInc(PF);
	reOrgEnergy = PFget_reOrg(PF);
	AttemptToHop = PFget_AttemptToHop(PF);
	gamma = PFget_gamma(PF);

	/*
	ReadParameter(&SLength, &SWidth, &SHeight,\
			&PeriodicX, &PeriodicY, &PeriodicZ,\
			&EndX, &EndY, &EndZ,\
			&XElecOn, &YElecOn, &ZElecOn,\
			&XFermiB, &XFermiF, &YFermiL,\
			&YFermiR, &ZFermiB, &ZFermiA,\
			&alphaxb, &alphaxf, &alphayl,\
			&alphayr, &alphazb, &alphaza,\
			&vX, &vY, &vZ,\
			&VoltageX, &VoltageY, &VoltageZ,\
			&VStepX, &VStepY, &VStepZ,\
			&VincX, &VincY, &VincZ,\
			&SiteDistance, &D, &TCount,\
			&NCh, &Ntot, &TStep, &N_av,\
			&Nstep_av, &Rcount, &CutOff,\
			&lambda, &SeedProt, &Attempts,\
			&fracSeed, &E0, &sigma,\
			&fracTrap, &Etrap, &Tsigma,\
			&TempStart, &TemperatureStep,\
			&TemperatureInc, &reOrgEnergy,\
			&AttemptToHop, &gamma,\
			&RelativePerm);
*/

	printf("Value of AttemptToHop %g\n",AttemptToHop);

	mem_check();
	int rN;
	int r;
	int count;
	int Vxcount;
	int Vycount;
	int Vzcount;

	double Vx;
	double Vy;
	double Vz;

	int OrderL;

	double KT;
	double Temperature;

	double electricFieldX;
	double electricFieldY;
	double electricFieldZ;

	double electricEnergyX;
	double electricEnergyY;
	double electricEnergyZ;

	Electrode elXb = NULL;
	Electrode elXf = NULL;
	Electrode elYl = NULL;
	Electrode elYr = NULL;
	Electrode elZb = NULL;
	Electrode elZa = NULL;

	double MarcusJ0;
	double MarcusCoeff;
	double SiteDistanceNM;

	matrix mtxmini;
	SNarray snAmini;

	char FileName[40];

	SNarray snA;
	ArbArray ClArLL;

	SiteDistanceNM = SiteDistance*1E9;
	rN = 1;
	Vx = VoltageX;
	Vxcount = 0;

	//Cycle through Xvoltages
	mem_check();
	while(Vxcount<=VStepX){
		Vy = VoltageY;
		Vycount = 0;

		//Cycle through Yvoltages
		while(Vycount<=VStepY){
			Vz = VoltageZ;
			Vzcount = 0;

			//Cycle through Zvoltages
			while(Vzcount<=VStepZ){

				for(count=0;count<TemperatureStep;count++){

					Temperature = TempStart;
					KT = kB*Temperature; 

					for(r=1;r<Rcount+1;r++){

						//Electric field from voltage
						electricFieldX = Vx / (SLength*SiteDistance);
						electricFieldY = Vy / (SWidth*SiteDistance);
						electricFieldZ = Vz / (SHeight*SiteDistance);

						//Electrical energy from voltage between two sites
						electricEnergyX = SiteDistance*electricFieldX;
						electricEnergyY = SiteDistance*electricFieldY;
						electricEnergyZ = SiteDistance*electricFieldZ;

						sprintf(FileName,"DataT%gVx%gVy%gVz%gR%d",Temperature,Vx,Vy,Vz,r);
						mem_check();
						//Anything created past this point must be deleted to prevent
						//memory leaks
						snA = newSNarray(SLength, SWidth, SHeight);	

						printf("After creating SNarray\n");
						mem_check();
						//Initialize Site Energies
						/*initSite(electricEnergyX, electricEnergyY, electricEnergyZ,\
								KT, reOrgEnergy, AttemptToHop, gamma, lambda, CutOff,\
								fracSeed, fracTrap, SiteDistance,\
								Etrap, Tsigma, E0, sigma, SeedProt,\
								PeriodicX, PeriodicY, PeriodicZ,\
								XElecOn, YElecOn, ZElecOn, snA);
						*/
						initSite(electricEnergyX, electricEnergyY, electricEnergyZ,\
										 KT, snA, PF);

						printf("After Init Site\n");
						mem_check();
						//Calculating Marcus J0 coefficient assuming the Attempt to hop Rate
						//is equivalent to the marcus coefficient at 300 K
						MarcusJ0 = pow( AttemptToHop*hbar*pow(4*reOrgEnergy*kB*300/M_PI,1/2),1/2);
						//Calculating full Marcus Coefficient;
						MarcusCoeff = pow(MarcusJ0,2)/hbar * pow(M_PI/(4*reOrgEnergy*KT),1/2)*exp(-2*gamma*SiteDistance);


						//Initialize Electrodes
						initElec(electricEnergyX, electricEnergyY, electricEnergyZ, MarcusCoeff,\
										 KT, snA,&elXb, &elXf, &elYl, &elYr, &elZb, &elZa, PF);

						printf("After Init Elec\n");
						mem_check();
						
						FindCluster( &OrderL, snA, electricEnergyX,\
												 electricEnergyY, electricEnergyZ,\
												 &ClArLL, KT, PF);
						
						//FindCluster(&OrderL, snA, electricEnergyX,\
						electricEnergyY, electricEnergyZ,\
							&ClArLL, KT, reOrgEnergy, Attempts,\
							PeriodicX, PeriodicY, PeriodicZ,\
							XElecOn, YElecOn, ZElecOn);

						//PrintFile_xyz(OrderL,snA, &ClArLL, &FileName[0]);
						//PrintNeighFile_xyz(OrderL,snA, &ClArLL, &FileName[0]);

						randomWalk(snA, rN, &FileName[0],\
								electricFieldX,	electricFieldY, electricFieldZ,\
								elXb, elXf, elYl, elYr, elZb, elZa, PF); 

						printf("Printing Visit Freq files\n");
						printVisitFreq(snA,&FileName[0]);

						//printArbArray(ClArLL, OrderL);

						deleteSNarray(snA);

						//Delete Electrodes
						if (elXb!=NULL){
							snAmini = (SNarray) getElectrode_AdjacentSites(elXb);
							deleteSNarray(snAmini);
							mtxmini = (matrix) getElectrode_HopRates(elXb);
							deleteMatrix(mtxmini);
							deleteElectrode(elXb);
							elXb = NULL;
						}
						if (elXf!=NULL){
							snAmini = (SNarray) getElectrode_AdjacentSites(elXf);
							deleteSNarray(snAmini);
							mtxmini = (matrix) getElectrode_HopRates(elXf);
							deleteMatrix(mtxmini);
							deleteElectrode(elXf);
							elXf = NULL;
						}

						if (elYl!=NULL){
							snAmini = (SNarray) getElectrode_AdjacentSites(elYl);
							deleteSNarray(snAmini);
							mtxmini = (matrix) getElectrode_HopRates(elYl);
							deleteMatrix(mtxmini);
							deleteElectrode(elYl);
							elYl = NULL;
						}
						if (elYr!=NULL){
							snAmini = (SNarray) getElectrode_AdjacentSites(elYr);
							deleteSNarray(snAmini);
							mtxmini = (matrix) getElectrode_HopRates(elYr);
							deleteMatrix(mtxmini);
							deleteElectrode(elYr);
							elYr = NULL;
						}
						if (elZb!=NULL){
							snAmini = (SNarray) getElectrode_AdjacentSites(elZb);
							deleteSNarray(snAmini);
							mtxmini = (matrix) getElectrode_HopRates(elZb);
							deleteMatrix(mtxmini);
							deleteElectrode(elZb);
							elZb = NULL;
						}

						if (elZa!=NULL){
							snAmini = (SNarray) getElectrode_AdjacentSites(elZa);
							deleteSNarray(snAmini);
							mtxmini = (matrix) getElectrode_HopRates(elZa);
							deleteMatrix(mtxmini);
							deleteElectrode(elZa);
							elZa = NULL;
						}


					}

					Temperature += TemperatureInc;
				}
				Vzcount++;
				Vz += VincZ;
			}
			Vycount++;
			Vy += VincY;
		}
		Vxcount++;
		Vx += VincX;
	}

	end = clock();
	time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
	time(&finish);
	//second = CPU_TIME;
	printf("Run Time %g seconds\n",time_spent);
	//printf("cpu : %.2f secs\n", second-first);
	printf("user : %d secs\n", (int)(finish-start));
						
	atexit(mem_term);

	return 0;
}
