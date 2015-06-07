package request;

import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-3-28
 * To change this template use File | Settings | File Templates.
 */
public class Base {

  public static Map<String,Object> putPublic(Map<String,Object> params,String action){
    params.put("zone","ac1");
    params.put("action",action);
    params.put("token", Constant.API_KEY);
    return params;
  }
}
