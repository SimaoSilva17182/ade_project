using Class_Library.Models;

var builder = WebApplication.CreateBuilder(args);

builder.Services.Configure<MongoDbSettings>(builder.Configuration.GetSection("MongoDb"));
builder.Services.AddSingleton<StudentServices>();

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();


var app = builder.Build();

app.MapGet("/", () => "Students API");

app.MapGet("/api/students", async (StudentServices studentService) =>
{
    var student = await studentService.GetAll();
    return Results.Ok(student);
});

app.MapGet("/api/students/{id}", async (StudentServices studentService, string id) =>
{
    var student = await studentService.Get(id);
    return student is null ? Results.NotFound() : Results.Ok(student);
});

app.MapPost("/api/students", async (StudentServices studentService, Student student) =>
{
    await studentService.Create(student);
    return Results.Ok();
});

app.MapPut("/api/students/{id}", async (StudentServices studentService, string id, Student updatedStudent) =>
{
    var student = await studentService.Get(id);
    if (student is null) return Results.NotFound();

    updatedStudent.Id = student.Id;
    await studentService.Update(id, updatedStudent);

    return Results.NoContent();
});

app.MapDelete("/api/students/{id}", async (StudentServices studentService, string id) =>
{
    var student = await studentService.Get(id);
    if (student is null) return Results.NotFound();

    await studentService.Remove(student.Id);

    return Results.NotFound();
});

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();

}

app.UseHttpsRedirection();

app.Run();
