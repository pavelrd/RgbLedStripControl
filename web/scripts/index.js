$( function()
{

    serverIP   = $("#inputServerIP").val()
    serverPort = $("#inputServerPort").val()
    
    $("#colorInput").iris({
        width: 400,
        hide:  false,
        change: function( event, ui )
        {
            
            console.log( ui.color.toString().substr(1) );

            var tmp = new Object();
            
            tmp['setCode'] = parseInt(ui.color.toString().substr(1), 16);
                            
            $.ajax(
            {
                url: "http://"+serverIP+":"+serverPort+"/",
                data: tmp,
                dataType: "json",
                timeout: 500,
                success: function(msg)
                {
                    
                },
                error: function(msg,a,b)
                {              
                }
            });
            
        }
    });
    
    
                                



   
});
