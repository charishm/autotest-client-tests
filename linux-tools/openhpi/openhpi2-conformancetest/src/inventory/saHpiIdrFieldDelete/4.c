/*      -*- linux-c -*-
 *
 * (C) Copyright IBM Corp. 2004, 2005
 *
 *   This program is free software; you can redistribute it and/or modify 
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or 
 *   (at your option) any later version.
 *   This program is distributed in the hope that it will be useful, 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *   GNU General Public License for more details. 
 *   You should have received a copy of the GNU General Public License 
 *   along with this program; if not, write to the Free Software 
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 
 *   USA 
 *
 * Author(s):
 *      Carl McAdams <carlmc@us.ibm.com>
 *      Donald A. Barre <dbarre@unh.edu>
 *
 * Spec:        HPI-B.01.01
 * Function:    saHpiIdrFieldDelete
 * Description:
 *   Call on a resource which does not support Inventory Data Repositories.
 *   Expected return: SA_ERR_HPI_CAPABILITY.
 * Line:        P113-19:P113-20
 *    
 */

#include <stdio.h>
#include "../include/inventory_test.h"

/***********************************************************************
 *
 * Try deleting a field for a resource that does not support inventories.
 *
 ***********************************************************************/

int deleteField(SaHpiSessionIdT sessionId, SaHpiResourceIdT resourceId)
{
	SaErrorT status;
	int retval;
	SaHpiEntryIdT AreaId = 1;
	SaHpiEntryIdT FieldId = 1;

	//   Call the routine on a resource which does not support IDRs.

	status = saHpiIdrFieldDelete(sessionId,
				     resourceId,
				     SAHPI_DEFAULT_INVENTORY_ID,
				     AreaId, FieldId);

	if (status == SA_ERR_HPI_CAPABILITY) {
		retval = SAF_TEST_PASS;
	} else {
		retval = SAF_TEST_FAIL;
		e_print(saHpiIdrFieldDelete, SA_ERR_HPI_CAPABILITY, status);
	}

	return retval;
}

/***********************************************************************
 *
 * Test a resource that does not support inventories.
 *
 ***********************************************************************/

int Test_Resource(SaHpiSessionIdT sessionId,
		  SaHpiRptEntryT report, callback2_t func)
{
	int retval = SAF_TEST_NOTSUPPORT;

	if (!hasInventoryCapability(&report)) {
		retval = deleteField(sessionId, report.ResourceId);
	}

	return retval;
}

/***********************************************************************
 *
 * Main Program
 *
 ***********************************************************************/

int main(int argc, char **argv)
{
	return process_all_domains(Test_Resource, NULL, NULL);
}
