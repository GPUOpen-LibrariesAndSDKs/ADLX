//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

import out.*;

// display list changed callback
public class DisplayListCallBack extends IADLXDisplayListChangedListener {
    
    public DisplayListCallBack(){
        super();
    }

    // override function
    public boolean OnDisplayListChanged(IADLXDisplayList pNewDisplay) {

        long size = pNewDisplay.Size();
        System.out.printf("\nDisplay list changed, the size of display list is: %d\n", size);
        long it = pNewDisplay.Begin();
        for(; it != pNewDisplay.Size(); it++){
            SWIGTYPE_p_p_adlx__IADLXDisplay ppDisplay = ADLX.new_displayP_Ptr();
            pNewDisplay.At(it, ppDisplay);
            IADLXDisplay display = ADLX.displayP_Ptr_value(ppDisplay);

            SWIGTYPE_p_p_char ppName = ADLX.new_charP_Ptr();
            display.Name(ppName);
            String name = ADLX.charP_Ptr_value(ppName);

            System.out.printf("the display [%d]:\n", it);
            System.out.printf("\tname: %s\n", name);

            display.Release();
        }

        return true;
    }
}
