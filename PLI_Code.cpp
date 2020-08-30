
#include "PLI_Code.h"

extern "C" __declspec(dllexport) PLI_INT32 my_hlf()
{

	//This handle could be assign so that it points to head of a circuit
	handle module_handle;
	srand(time(NULL));

	acc_initialize();
	io_printf("PLI_Start\n");

	module_handle = acc_handle_tfarg(1); 

	//test
	PLI_BYTE8 * name;
	name = acc_fetch_fullname(module_handle);
	io_printf("%s\n",name);
	//
	
	
	//display names of all nets in current level of module
	handle net_handle;
	net_handle = null; 
	

	//an example for changing value of a net
	static s_setval_value value_s;// = {accBinStrVal};
	value_s.format = accScalarVal;
	static s_setval_delay delay_s = {{accRealTime},accInertialDelay};
	delay_s.time.real= 0.0;
	delay_s.model = accForceFlag;
	
	/*PART 3 & 4*/
	/*
	for (int x = 0; x < 5; x++){
		int r = (rand() % 47);
		net_handle = null;
		for (int y = 0; y <= r; y++){
			net_handle = acc_next_net(module_handle, net_handle);
			//print value of value_s
			//io_printf("Value of Values = %d \n", value_s.value.scalar);
			if (y==r){
				//print net name
				io_printf("Net name is: %s\n", acc_fetch_fullname(net_handle));
				//print value of net
				io_printf("Net value is: %s\n", acc_fetch_value(net_handle, "%b", null));
				//move value of net to value_s
				acc_fetch_value(net_handle, "%%", &value_s);
				//set value_s to another number
				if (value_s.value.scalar == acc0)
					value_s.value.scalar = acc1;
				else
					value_s.value.scalar = acc0;
				//set net value to value of value_s
				acc_set_value(net_handle, &value_s, &delay_s);
				//read value of net
				io_printf("New Net value is: %s\n", acc_fetch_value(net_handle, "%b", null));
				break;
			}
		}
	}
	
	*/

	//prints name of all child from top to down
	handle temp[20] = {null};
	temp[0] = module_handle;
	int i = 0, f = 0;
	int j = 0;
	int faults = 5;

	/* part 5 */

	/*while (temp[i] != null) {
		handle child = null;
		while (child = acc_next_child(temp[i], child)) {
			j++;
			temp[j] = child;
			//io_printf("%40s\n", acc_fetch_fullname(temp[j]));
			while (net_handle = acc_next_net(child, net_handle)) {
				
				if (strcmp(acc_fetch_fullname(child), "SayehTest.U1.ctrl") == 0) {
					//bit_indx = 0;
					while (f < faults){
						net_handle = null;
						while (net_handle = acc_next_net(module_handle, net_handle)) {
							int r = (rand() % 1000);
							if (r > 300 && r <=500) {
								if (f < faults) {
									io_printf("Befor: %s: %s\n", acc_fetch_fullname(net_handle), acc_fetch_value(net_handle, "%b", null));
									acc_fetch_value(net_handle, "%%", &value_s);
									if (value_s.value.scalar == acc1)
										value_s.value.scalar = acc0;
									else
										value_s.value.scalar = acc1;
									f++;
									acc_set_value(net_handle, &value_s, &delay_s);
									io_printf("After: %s: %s\n", acc_fetch_fullname(net_handle), acc_fetch_value(net_handle, "%b", null));
								}
							}
						}
					}
				}
			}
		}
		i++;
	}*/
	
	

	acc_close();
	return 0;
}

 extern "C" __declspec(dllexport) s_tfcell veriusertfs[]=
{
	{usertask, 0, 0, 0, my_hlf, 0, "$my_hlf"},
	{0}
};