struct TrackMeta {
  1: i32 trackID,
  2: string creator,
  3: string modifier,
  4: string uri
}


struct VersionMeta {
  1: i32 versionID,
  2: list<TrackMeta> tracks
}


struct ProjectMeta {
  1: string name,
  2: list<string> owners,
  3: list<string> collaborators,
  4: list<VersionMeta> versions
}


service MasterServer {
  ProjectMeta getProjectMeta(1:string name),
  VersionMeta getVersionMeta(2:i32 versionID),
  VersionMeta getLastestVersionMeta(3:string name),
}
