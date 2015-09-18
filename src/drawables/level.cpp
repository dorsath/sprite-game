#include "../config.hpp"

Level::Level(std::string file){
  filename_ = file;
  load();
}

void Level::save(){
  for (Chunk* chunk: chunks){
    chunk->save();
  }

  std::ofstream datafile(filename_, std::ios::binary);
  datafile.write((char*)&data_[0], data_.size() * sizeof(ChunkData));
  datafile.close();
}

void Level::load(){
  std::ifstream datafile(filename_, std::ios::binary);

  datafile.seekg(0, std::ios::end);
  int numberOfChunks = datafile.tellg() / sizeof(ChunkData);
  datafile.seekg(0, std::ios::beg);

  ChunkData buffer[numberOfChunks];
  datafile.read((char*)buffer, numberOfChunks * sizeof(ChunkData));

  datafile.close();

  data_.insert(data_.begin(), buffer, buffer + numberOfChunks);
}

void Level::setTexture(Texture* texture){
  texture_ = texture;
}
  

void Level::draw(float dt){
  for (Chunk* chunk: chunks){
    chunk->draw(dt);
  }
} 

Chunk* Level::findChunk(Vec2 position){
  for (ChunkData chunkData: data_){
    if (Vec2(chunkData.x, chunkData.y) == position){
      std::cout << "found chunk" << std::endl;
      return loadChunk(chunkData);
    }
  }

  std::cout << "no chunk found, new chunk coming up" << std::endl;

  ChunkData newChunkData;
  newChunkData.x = position.x;
  newChunkData.y = position.y;
  newChunkData.n = data_.size() + 1;
  data_.push_back(newChunkData);
  return loadChunk(newChunkData);
}

Chunk* Level::loadChunk(ChunkData chunkData){
  std::string chunkPath = "./resources/level_1/";
  std::stringstream fmt; 
  fmt << chunkPath << chunkData.n << ".dat";
  std::string filepath = fmt.str();
  std::cout << "Loading: " << filepath << " " << chunkData.x << ":" << chunkData.y << std::endl;

  Chunk* chunk = new Chunk(filepath, Vec2(chunkData.x, chunkData.y));
  chunk->setTexture(texture_);
  chunk->setup();
  return chunk;
}


void Level::setup(){
  for (ChunkData chunkData: data_){
    Chunk* chunk = loadChunk(chunkData);
    chunks.push_back(chunk);
  }
}
