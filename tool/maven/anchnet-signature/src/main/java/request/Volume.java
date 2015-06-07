package request;

import java.util.HashMap;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: anchnet-002
 * Date: 15-3-29
 * To change this template use File | Settings | File Templates.
 */
public class Volume {

  public static Map<String,Object> createVolumes(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("volume_name","cloud3_ccvv_hd");
    map.put("count",1);
    map.put("size",10);
    map.put("volume_type",1);
    //        map.put("project","pro-V9HBDSCW");
    return Base.putPublic(map, "CreateVolumes");
  }

  public static Map<String,Object> describeVolumes(){
    Map<String,Object> map = new HashMap<String, Object>();
    //        map.put("volumes",new String[]{"vol-3P55VY7Z"});
    //        map.put("status","available");
    map.put("search_word","t2");
    //        map.put("verbose",1);
    //        map.put("offset","");
    //        map.put("limit","");
    //        map.put("project",81);
    return Base.putPublic(map, "DescribeVolumes");
  }

  public static Map<String,Object> attachVolumes(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("volumes",new String[]{"vom-KWTGBLSB"});
    map.put("instance","i-MHV0M73W");
    map.put("project",86);
    return Base.putPublic(map, "AttachVolumes");
  }

  public static Map<String,Object> detachVolumes(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("volumes",new String[]{"vom-KWTGBLSB"});
    return Base.putPublic(map, "DetachVolumes");
  }

  public static Map<String,Object>  resizeVolumes(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("volumes",new String[]{"vom-M281SDJW"});
    map.put("size",20);
    return Base.putPublic(map, "ResizeVolumes");
  }

  public static Map<String,Object> deleteVolumes(){
    Map<String,Object> map = new HashMap<String,Object>();
    map.put("volumes",new String[]{"vom-BCB4I315"});
    return Base.putPublic(map, "DeleteVolumes");
  }

  public static Map<String,Object> modifyVolumeAttributes(){
    Map<String,Object> map = new HashMap<String, Object>();
    map.put("volume","vom-X7TBDRR5");
    map.put("volume_name","cloud3_ccvvsub_hd");
    map.put("description","test");
    map.put("project","pro-4QZCAFFW");
    return Base.putPublic(map, "ModifyVolumeAttributes");
  }
}
