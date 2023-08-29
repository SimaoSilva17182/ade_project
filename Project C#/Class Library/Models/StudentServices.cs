using Microsoft.Extensions.Options;
using MongoDB.Driver;
using MongoDB.Bson;

namespace Class_Library.Models
{
    public class StudentServices
    {
        private readonly IMongoCollection<Student> _studentCollection;


        public StudentServices(IOptions<MongoDbSettings> mongoDbSettings)
        {
            MongoClient client = new MongoClient(mongoDbSettings.Value.ConnectionURI);
            IMongoDatabase database = client.GetDatabase(mongoDbSettings.Value.DatabaseName);
            _studentCollection = database.GetCollection<Student>(mongoDbSettings.Value.CollectionName);
        }

        public async Task <List<Student>> GetAll() => 
            await _studentCollection.Find(student => true).ToListAsync();
        public async Task<Student> Get(string id) =>
            await _studentCollection.Find(student => student.Id == id).FirstOrDefaultAsync();
        public async Task Create(Student newStudent) =>
            await _studentCollection.InsertOneAsync(newStudent);
        public async Task Remove(string id) => 
            await _studentCollection.DeleteOneAsync(student => student.Id == id);
        public async Task Update(string id, Student student) => 
            await _studentCollection.ReplaceOneAsync(student => student.Id == id, student);

    }
}
