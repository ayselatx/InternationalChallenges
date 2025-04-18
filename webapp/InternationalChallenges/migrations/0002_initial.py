# Generated by Django 5.1.6 on 2025-03-21 09:04

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        ("InternationalChallenges", "0001_initial"),
    ]

    operations = [
        migrations.CreateModel(
            name="SensorData",
            fields=[
                (
                    "id",
                    models.BigAutoField(
                        auto_created=True,
                        primary_key=True,
                        serialize=False,
                        verbose_name="ID",
                    ),
                ),
                ("temperature", models.FloatField()),
                ("humidity", models.FloatField()),
                ("timestamp", models.DateTimeField(auto_now_add=True)),
            ],
        ),
    ]
