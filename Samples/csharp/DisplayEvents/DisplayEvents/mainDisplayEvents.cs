// 
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace DisplayEvents
{
    class mainDisplayEvents
    {
        static void Main(string[] args)
        {
            // Initialize ADLX with ADLXHelper
            ADLXHelper help = new ADLXHelper();
            ADLX_RESULT res = help.Initialize();

            if (res == ADLX_RESULT.ADLX_OK)
            {
                // Get system services
                IADLXSystem sys = help.GetSystemServices();

                if (sys != null)
                {
                    // Get display services
                    SWIGTYPE_p_p_adlx__IADLXDisplayServices s = ADLX.new_displaySerP_Ptr();
                    res = sys.GetDisplaysServices(s);
                    IADLXDisplayServices displayService = ADLX.displaySerP_Ptr_value(s);

                    if (res == ADLX_RESULT.ADLX_OK)
                    {
                        // Get displaychangedhandling
                        SWIGTYPE_p_p_adlx__IADLXDisplayChangedHandling ppDisChangeHand = ADLX.new_displayChangeHandlP_Ptr();
                        res = displayService.GetDisplayChangedHandling(ppDisChangeHand);
                        IADLXDisplayChangedHandling hand = ADLX.displayChangeHandlP_Ptr_value(ppDisChangeHand);

                        if (res == ADLX_RESULT.ADLX_OK)
                        {
                            // Callback for displayListChanged
                            DisplayListCallBack call = new DisplayListCallBack();
                            hand.AddDisplayListEventListener(call);
                            Console.WriteLine(String.Format("\n\n Plug or unplug a display within 20 seconds."));
                            try
                            {
                                Thread.Sleep(20000);
                            }
                            catch (Exception e)
                            {
                                // Exception
                            }
                            hand.RemoveDisplayListEventListener(call);

                            // Release display change handling interface
                            hand.Release();
                        }

                        // Release display services interface
                        displayService.Release();
                    }
                }
            }
            else
            {
                Console.WriteLine(String.Format("ADLX helper initialization result: {0}", res));
            }

            // Terminate ADLX
            res = help.Terminate();
            Console.WriteLine(String.Format("ADLX Terminate result: {0}", res));
            Console.ReadKey();
        }
    }

    // Callback for display list changed
    public class DisplayListCallBack : IADLXDisplayListChangedListener
    {
        public DisplayListCallBack()
            :base(){}

        // Override function
        public override bool OnDisplayListChanged(IADLXDisplayList pNewDisplay)
        {
            uint size = pNewDisplay.Size();
            Console.WriteLine(String.Format("\nDisplay list changed, display list size: {0}", size));
            uint it = pNewDisplay.Begin();
            for (; it != pNewDisplay.Size(); it++)
            {
                SWIGTYPE_p_p_adlx__IADLXDisplay ppDisplay = ADLX.new_displayP_Ptr();
                pNewDisplay.At(it, ppDisplay);
                IADLXDisplay display = ADLX.displayP_Ptr_value(ppDisplay);

                SWIGTYPE_p_p_char ppName = ADLX.new_charP_Ptr();
                display.Name(ppName);
                String name = ADLX.charP_Ptr_value(ppName);

                Console.WriteLine(String.Format("The display [{0}]:", it));
                Console.WriteLine(String.Format("\tname: {0}", name));

                display.Release();
            }

            return true;
        }
    }
}
