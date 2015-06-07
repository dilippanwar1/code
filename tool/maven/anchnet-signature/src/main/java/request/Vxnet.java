package request;

import java.util.HashMap;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-3-29
 * To change this template use File | Settings | File Templates.
 */
public class Vxnet {

  public static Map<String,Object> createVxnets(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("vxnet_name","cloud3_1_net");
    map.put("vxnet_type",0);
    map.put("count",1);
    map.put("project",86);
    return Base.putPublic(map,"CreateVxnets");
  }

  public static Map<String,Object> deleteVxnets(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("vxnets",new String[]{"vxnet-J6AT0AKX"});

    //        vxnet-HWVTAFSG
    //        vxnet-2QZZZUH5

    //        vxnet-RGIT1KT8
    //        vxnet-HZSFANVM

    //        ,"vxnet-2OQBTMR3","vxnet-WYC0G78R","vxnet-MENHUFNN"
    //        map.put("project",81);
    return Base.putPublic(map,"DeleteVxnets");
  }

  public static Map<String,Object> joinVxnet(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("vxnet","vxnet-2V559W86");

    map.put("instance",new String[]{"i-MHV0M73W"});
    return Base.putPublic(map,"JoinVxnet");
  }

  public static Map<String,Object> leaveVxnet(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("vxnet","vxnet-0");
    map.put("instances",new String[]{"i-Q9PTUJ7Q"});
    return Base.putPublic(map,"LeaveVxnet");
  }

  public static Map<String,Object> describeVxnets(){
    Map<String,Object> map = new HashMap<String, Object>();
    //        map.put("vxnets",new String[]{"vxnet-6X3ECEA9","vxnet-2SQTDNCK","vxnet-VZC4IURK"});
    //        map.put("search_word","gao_");
    //        map.put("offset","");
    //        map.put("limit","");
    map.put("vxnets","vxnet-0");
    map.put("verbose",1);
    //        map.put("project",86);
    return Base.putPublic(map,"DescribeVxnets");
  }

}
